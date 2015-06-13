#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "server.h"
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
    printf("%s\n%s\n%s\n%s\n%s\n", "Command List",
           "    help            -- displays list of commands",
           "    exit            -- terminates the server",
           "    kick [username] -- kicks a player",
           "    ls-clients      -- lists connected clients");
}
int server(int num_players, int port)
{
    Server server;
    init_server(&server, port, num_players);
    
    Command command;
    command.created = false;
    pthread_t command_thread;
    pthread_create(&command_thread, 0, accept_command, &command);
    printf("Type commands below...\n");
    
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
                char temp[20];
                memcpy(temp, command.second_arg, 20 * sizeof(char));
                kick_client(&server, temp);
            }
            else if(strcmp(command.first_arg, "ls-clients") == 0)
                print_client_list(&server);
            else
                printf("%s '%s'. %s", "ERROR: Invalid command",
                       command.first_arg, "Type 'help' for command list\n");
            command.created = false;
            pthread_create(&command_thread, 0, accept_command, &command);
        }
        sync_server_with_clients(&server);
    }
    printf("Exiting server..\n");
    free_server(&server);
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
