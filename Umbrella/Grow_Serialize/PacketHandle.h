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
#include "PacketHandle.h"
#include "../enet/include/enet.h"
#include "../proton/rtparam.hpp"
#include "../xorstr.hpp"
#include "../HTTPRequest.hpp"

using namespace std;

void GrowtopiaBot::ProcessPacket(ENetEvent* event, ENetPeer* peer)
	{
		int messageType = GetMessageTypeFromPacket(event->packet);
		
		switch (messageType) {
		case 1:
			onLoginRequested();
			break;
		default:
			packet_unknown(event->packet);
			break;
		case 3:
			packet_type3(GetTextPointerFromPacket(event->packet));
			break;
		case 4:
		{
			BYTE* tankUpdatePacket = GetStructPointerFromTankPacket(event->packet);
			if (tankUpdatePacket)
			{
				ProcessTankUpdatePacket(tankUpdatePacket, event->packet);
			}
			else {
				cout << "Got bad tank packet";
			}
		}
		break;
		case 5:
			break;
		case 6:
			packet_type6(GetTextPointerFromPacket(event->packet));
			break;
		}
	}
	
	
	BYTE* GrowtopiaBot::GetStructPointerFromTankPacket(ENetPacket* packet)
	{
		unsigned int packetLenght = packet->dataLength;
		BYTE* result = NULL;
		if (packetLenght >= 0x3C)
		{
			BYTE* packetData = packet->data;
			result = packetData + 4;

			if (*(BYTE*)(packetData + 16) & 8)
			{
				cout << "Is zero!" << *(int*)(packetData + 56) << endl;
				if (packetLenght < *(int*)(packetData + 56) + 60)
				{
					cout << "Packet too small for extended packet to be valid" << endl;
					cout << "Sizeof float is 4.  TankUpdatePacket size: 56" << endl;
					result = 0;
				}
			}
			else
			{
				int zero = 0;
				memcpy(packetData + 56, &zero, 4);
			}
		}
		return result;
	}
	
	void GrowtopiaBot::ProcessTankUpdatePacket(BYTE* structPointer, ENetPacket* packets)
	{
		auto packetd = get_struct(packets);
		packetprint(packetd);
		cout << "Processing tank packet with id of: " << +(*(char*)structPointer) << " Where first byte is " << std::to_string(structPointer[0]) << endl;
		HandlePacket(structPointer, packets);
	}



gameupdatepacket_t* GrowtopiaBot::get_struct(ENetPacket* packet) {
		if (packet->dataLength < sizeof(gameupdatepacket_t) - 4)
			return nullptr;
		gametankpacket_t* tank = reinterpret_cast<gametankpacket_t*>(packet->data);
		gameupdatepacket_t* gamepacket = reinterpret_cast<gameupdatepacket_t*>(packet->data + 4);
		if (gamepacket->m_packet_flags & 8) {
			if (packet->dataLength < gamepacket->m_data_size + 60) {
				printf("got invalid packet. (too small)\n");
				return nullptr;
			}
			return reinterpret_cast<gameupdatepacket_t*>(&tank->m_data);
		}
		else
			gamepacket->m_data_size = 0;
		return gamepacket;
	}


void GrowtopiaBot::HandlePacket(BYTE* structPointer, ENetPacket* packets){
	switch (*(char*)structPointer) {
            case PACKET_STATE: break;
            case PACKET_CALL_FUNCTION: OnCallFunction(structPointer, packets); break; // use
            case PACKET_UPDATE_STATUS: break;
            case PACKET_TILE_CHANGE_REQUEST: OnTileChangeRequest(structPointer, packets); break; // use
            case PACKET_SEND_MAP_DATA: OnSendMapData(structPointer, packets); break; // use
            case PACKET_SEND_TILE_UPDATE_DATA: break;
            case PACKET_SEND_TILE_UPDATE_DATA_MULTIPLE:  break;
            case PACKET_TILE_ACTIVATE_REQUEST: OnTileActivateRequest(structPointer, packets); break; // use
            case PACKET_TILE_APPLY_DAMAGE: break;
            case PACKET_SEND_INVENTORY_STATE: OnSendInventoryState(structPointer, packets); break; // use
            case PACKET_ITEM_ACTIVATE_REQUEST: break;
            case PACKET_ITEM_ACTIVATE_OBJECT_REQUEST: break;
            case PACKET_SEND_TILE_TREE_STATE: OnSendTileTreeState(structPointer, packets); break; // use
            case PACKET_MODIFY_ITEM_INVENTORY: OnModifyItemInventory(structPointer, packets); break; // use
            case PACKET_ITEM_CHANGE_OBJECT: OnItemChangeObject(structPointer, packets); break; // use
            case PACKET_SEND_LOCK: break;
            case PACKET_SEND_ITEM_DATABASE_DATA: OnSendItemDatabaseData(structPointer, packets); break; // use
            case PACKET_SEND_PARTICLE_EFFECT: break;
            case PACKET_SET_ICON_STATE: break;
            case PACKET_ITEM_EFFECT: break;
            case PACKET_SET_CHARACTER_STATE: break;
            case PACKET_PING_REPLY: break; 
            case PACKET_PING_REQUEST: OnPingRequest(structPointer, packets); break; // use 
            case PACKET_GOT_PUNCHED: break;
            case PACKET_APP_CHECK_RESPONSE: break;
            case PACKET_APP_INTEGRITY_FAIL: break;
            case PACKET_DISCONNECT: break;
            case PACKET_BATTLE_JOIN: break;
            case PACKET_BATTLE_EVEN: break;
            case PACKET_USE_DOOR: break;
            case PACKET_SEND_PARENTAL: break;
            case PACKET_GONE_FISHIN: break;
            case PACKET_STEAM: break;
            case PACKET_PET_BATTLE: break;
            case PACKET_NPC: break;
            case PACKET_SPECIAL: break;
            case PACKET_SEND_PARTICLE_EFFECT_V2: break;
            case GAME_ACTIVE_ARROW_TO_ITEM: break;
            case GAME_SELECT_TILE_INDEX: break;
            default: break;
        }
}