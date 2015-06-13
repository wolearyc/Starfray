#ifndef PACKET_H
#define PACKET_H
#include <string.h>
#include "entity.h"
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
enum PacketType
{
    /* server and client */
    UPDT_ENTITY,
    REMOVE_ENTITY,
    
    /* server */
    REQUEST_CONNECTION,
    CONFIRM_CONNECTION,
    REJECT_CONNECTION,
    END_CONNECTION,
    
    /* client */
    NEW_CONNECTION,
    ENDED_CONNECTION,
    USERNAME_INFO,
    KICKED,
};
typedef struct Packet
{
    enum PacketType type;
    char data[64];
} Packet;
Packet get_updt_entity_packet(Entity* entity);
void parse_updt_entity_packet(Packet* packet, Entity* entity);
Packet get_remove_entity_packet(Entity* entity);
void parse_remove_entity_packet(Packet* packet, Entity* entity);
Packet get_request_connection_packet(char* username);
void parse_request_connection_packet(Packet* packet, char* username);
Packet get_confirm_connection_packet(int client_id, int max_clients);
void parse_confirm_connection_packet(Packet* packet, int* client_id,
                                     int* max_clients);
Packet get_username_info_packet(char* username, int client_id);
void parse_username_info_packet(Packet* packet, char* username, int* client_id);
Packet get_new_connection_packet(char* username, int client_id);
void parse_new_connection_packet(Packet* packet, char* username,
                                 int* client_id);
Packet get_reject_connection_packet();
Packet get_end_connection_packet();
Packet get_ended_connection_packet(int client_id);
void parse_ended_connection_packet(Packet* packet, int* client_id);
Packet get_kicked_packet(int client_id);
void parse_kicked_packet(Packet* packet, int* client_id);
#endif