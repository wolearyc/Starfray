#include "wic_lib.h"
#include <stdio.h>
#include <pthread.h>
#include "entity_manager.h"
#include "packets.h"
typedef struct Command
{
    char first_arg[50];
    char second_arg[50];
    bool created;
} Command;
void* accept_command(void* pointer)
{
    Command* command = (Command*) pointer;
    memset(command->first_arg, 0, sizeof(command->first_arg));
    memset(command->second_arg, 0, sizeof(command->second_arg));
    size_t temp_size = 50;
    char* temp = malloc(sizeof(char) * temp_size);
    while(true)
    {
        memset(temp, 0, temp_size * sizeof(char));
        size_t num_chars = getline(&temp, &temp_size, stdin);
        if(num_chars > temp_size)
            printf("ERROR: Invalid command. Type 'help' for command list\n");
        if(num_chars != 0 && temp[0] != '\n')
            break;
    }
    sscanf(temp, " %s %s ", command->first_arg, command->second_arg);
    command->created = true;
    free(temp);
    return 0;
}
void print_command_list()
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "Command List",
           "    help                    -- displays list of commands",
           "    exit                    -- terminates the server",
           "    kick [username]         -- kicks a client",
           "    ban-client [username]   -- bans a client",
           "    ban-address [address]   -- bans an IP address",
           "    unban-address [address] -- unbans an IP address",
           "    ls-clients              -- lists connected clients");
}
typedef struct ClientData
{
    bool joined;
    unsigned char client_id;
    EntityManager manager;
    char username[20];
} ClientData;
void print_clients(ClientData* clients, unsigned char num_clients)
{
    printf("Client List\n");
    for(unsigned char i; i < num_clients; i++)
    {
        if(clients[i].joined)
            printf("%20s\n", clients[i].username);
    }
}
ClientData* lookup_client(ClientData* clients, char username[],
                          unsigned char num_clients)
{
    for(unsigned char i = 0; i < num_clients; i++)
    {
        if(strcmp(clients[i].username, username) == 0)
            return &clients[i];
    }
    return 0;
}
int server(int num_clients, int port)
{
    WicServer server;
    wic_init_server(&server, port, num_clients);
    ClientData* clients = malloc(num_clients * sizeof(ClientData));
    for(int i = 0; i < num_clients; i++)
        clients[i].joined = false;
    
    Command command;
    command.created = false;
    pthread_t command_thread;
    pthread_create(&command_thread, 0, accept_command, &command);
    printf("Type commands below...\n");
    
    WicPacket recv;
    WicPacket send;
    while(true)
    {
        if(command.created == true)
        {
            if(strncmp(command.first_arg, "exit", 4) == 0)
                break;
            else if(strcmp(command.first_arg, "help") == 0)
                print_command_list();
            else if(strcmp(command.first_arg, "kick") == 0)
            {
                ClientData* client = lookup_client(clients, command.second_arg,
                                                   num_clients);
                if(client == 0)
                    printf("ERROR: Client %s does not exist\n",
                           command.second_arg);
                else
                    wic_kick_client(&server, client->client_id);
            }
            else if(strcmp(command.first_arg, "ban-client") == 0)
            {
                ClientData* client = lookup_client(clients, command.second_arg,
                                                   num_clients);
                if(client == 0)
                    printf("ERROR: Client %s does not exist\n",
                           command.second_arg);
                else
                    wic_ban_client(&server, client->client_id);
            }
            else if(strcmp(command.first_arg, "ban-address") == 0)
            {
                wic_ban_address(&server, command.second_arg);
            }
            else if(strcmp(command.first_arg, "unban-address") == 0)
            {
                wic_unban_address(&server, command.second_arg);
            }
            else if(strcmp(command.first_arg, "ls-clients") == 0)
            {
                print_clients(clients, num_clients);
            }
            else
                printf("%s '%s'. %s", "ERROR: Invalid command",
                       command.first_arg, "Type 'help' for command list\n");
            command.created = false;
            pthread_create(&command_thread, 0, accept_command, &command);
        }
        enum WicError error = wic_server_recv_packet(&server, &recv);
        if(error == WICER_NONE)
        {
            unsigned char client_id = recv.client_id;
            if(recv.type.id == WIC_PACKET_JOIN.id)
            {
                clients[client_id].joined = true;
                clients[client_id].client_id = client_id;
                init_entity_manager(&clients[client_id].manager);
                printf("client %u joined\n", client_id);
            }
            if(recv.type.id == PACKET_USERNAME_INFO.id)
            {
                memcpy(clients[client_id].username, recv.data,
                       PACKET_USERNAME_INFO.size);
                wic_send_packet_to_other_clients(&server, &recv, client_id);
                for(unsigned char id = 0; id < num_clients; id++)
                {
                    if(clients[id].joined && id != client_id)
                    {
                        send.type = PACKET_USERNAME_INFO;
                        send.client_id = id;
                        memcpy(send.data, clients[id].username,
                               sizeof(clients[id].username));
                        wic_send_packet_to_client(&server, &send, client_id);
                    }
                }
            }
            else if(recv.type.id == WIC_PACKET_LEAVE.id)
            {
                clients[client_id].joined = false;
                free_entity_manager(&clients[client_id].manager);
                printf("client %u left\n", recv.client_id);
            }
            else if(recv.type.id == PACKET_UPDT_ENTITY.id)
            {
                Entity entity;
                memcpy(&entity, recv.data, PACKET_UPDT_ENTITY.size);
                updt_entity(&clients[client_id].manager, entity);
                wic_send_packet_to_other_clients(&server, &recv, client_id);
            }
            else if(recv.type.id == PACKET_REMV_ENTITY.id)
            {
                remove_entity(&clients[client_id].manager, recv.data[0]);
                wic_send_packet_to_other_clients(&server, &recv, client_id);
            }
        }
    }
    printf("Exiting server..\n");
    wic_free_server(&server);
    return 0;
}
int main(int argc, char** argv)
{
    printf("-- Starfray Server -- \n");
    int num_players = 0;
    while(true)
    {
        printf("Number of players? (1-100) : ");
        int result = scanf("%i", &num_players);
        char* temp;
        size_t temp_length = sizeof(char);
        getline(&temp, &temp_length, stdin);
        if(num_players > 0 && num_players <= 100 && result == 1)
            break;
        else
            printf("%s%s", "ERROR: Number of players must be between 1 and",
                   " 100 (inclusive).\n");
    }
    int port = 1111;
    while(false)
    {
        printf("Port? (1025-50000) : ");
        int result = scanf("%i", &port);
        char* temp;
        size_t temp_length = sizeof(char);
        getline(&temp, &temp_length, stdin);
        if(port >= 1025 && port <= 50000 && result == 1)
            break;
        else
            printf("%s%s", "ERROR: Port must be between 1025 and 50000",
                   " (inclusive).\n");
    }
    return server(num_players, port);
}