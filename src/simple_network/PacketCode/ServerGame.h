#pragma once
#include "ServerNetwork.h"
#include "NetworkData.h"
#include "../../src/Savegame/BattleUnit.h"

class ServerGame
{

public:

    ServerGame(void);
    ~ServerGame(void);

    void update();

	void receiveFromClients();

	void sendActionPackets();

	void unpackKneelPacket(Packet KneelPacket, int id);

	void sendKneelPackets(int id);

private:

   // IDs for the clients connecting for table in ServerNetwork 
    static unsigned int client_id;

   // The ServerNetwork object 
    ServerNetwork* network;

	// data buffer
   char network_data[MAX_PACKET_SIZE];
};
