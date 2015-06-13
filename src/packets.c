#include "packets.h"
const WicPacketType PACKET_USERNAME_INFO = {6, sizeof(char[20])};
const WicPacketType PACKET_UPDT_ENTITY = {7, sizeof(Entity)};
const WicPacketType PACKET_REMV_ENTITY = {8, 1};