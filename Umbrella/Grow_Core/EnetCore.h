#pragma once
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <regex>
#include <iterator>
#include <algorithm>
#include <ctime>
#include "../utilsfunc.h"
#include "../corefunc.h"
#include "EnetCore.h"
#include "../enet/include/enet.h"
#include "../proton/rtparam.hpp"
#include "../xorstr.hpp"
#include "../HTTPRequest.hpp"

using namespace std;
	void GrowtopiaBot::SendPacket(int a1, string a2, ENetPeer* enetPeer)
		{
			if (enetPeer)
			{
				ENetPacket* v3 = enet_packet_create(0, a2.length() + 5, 1);
				memcpy(v3->data, &a1, 4);
				//*(v3->data) = (DWORD)a1;
				memcpy((v3->data) + 4, a2.c_str(), a2.length());

				//cout << std::hex << (int)(char)v3->data[3] << endl;
				enet_peer_send(enetPeer, 0, v3);
			}
		}

	void GrowtopiaBot::SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
	{
		ENetPacket* p;

		if (peer) // check if we have it setup
		{
			if (a1 == 4 && *((BYTE*)packetData + 12) & 8)
			{
				p = enet_packet_create(0, packetDataSize + *((DWORD*)packetData + 13) + 5, packetFlag);
				int four = 4;
				memcpy(p->data, &four, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				memcpy((char*)p->data + packetDataSize + 4, a4, *((DWORD*)packetData + 13));
				enet_peer_send(peer, 0, p);
			}
			else
			{
				p = enet_packet_create(0, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy((char*)p->data + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
		}
	}
	
	void GrowtopiaBot::Disconnect() {
	enet_peer_disconnect(peer, 0);	
	}

	// Connect with default value
	void GrowtopiaBot::connectClient() {
		connectClient(SERVER_HOST, SERVER_PORT);
	}

	void GrowtopiaBot::connectClient(string hostName, int port)
	{
		cout << "Connecting bot to " << hostName << ":" << port << endl;
		client = enet_host_create(NULL,
			1,
			2,
			0,
			0);
		client->usingNewPacket = true;
		if (client == NULL)
		{
			cout << "An error occurred while trying to create an ENet client host.\n";

			exit(EXIT_FAILURE);
		}
		ENetAddress address;

		client->checksum = enet_crc32;
		enet_host_compress_with_range_coder(client);
		enet_address_set_host(&address, hostName.c_str());
		address.port = port;

		peer = enet_host_connect(client, &address, 2, 0);
		if (peer == NULL)
		{
			cout << "No available peers for initiating an ENet connection.\n";

			exit(EXIT_FAILURE);
		}
		enet_host_flush(client);
	}
	
	void GrowtopiaBot::eventLoop()
	{
		ENetEvent event;
		while (enet_host_service(client, &event, 0) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_NONE:
				cout << "No event???" << endl;
				break;
			case ENET_EVENT_TYPE_CONNECT:
				WhenConnected();
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				WhenDisconnected();
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				ProcessPacket(&event, peer);
				enet_packet_destroy(event.packet);
				break;
			default:
				cout << "WTF???" << endl;
				break;
			}
		}
		//userLoop();
	}