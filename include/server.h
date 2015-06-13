#ifndef SERVER_H
#define SERVER_H
#include "entity.h"
#include "packet.h"
#include "entity_manager.h"
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>
struct Client;
typedef struct Server
{
    int socket;
    struct sockaddr_in address;
    socklen_t address_length;
    char sendBuffer[sizeof(Packet)];
    char receiveBuffer[sizeof(Packet)];
    struct Client* clients;
    int max_clients;
} Server;
bool init_server(Server* target, int port, int max_connections);
void kick_client(Server* server, char* username);
void print_client_list(Server* server);
void sync_server_with_clients(Server* target);
void free_server(Server* target);
#endif