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
#include "utilsfunc.h"
#include "corefunc.h"
#include "userfunc.h"
#include "enet/include/enet.h"
#include "proton/rtparam.hpp"
#include "xorstr.hpp"
#include "HTTPRequest.hpp"

using namespace std;

char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string hexStr(unsigned char data)
{
	std::string s(2, ' ');
	s[0] = hexmap[(data & 0xF0) >> 4];
	s[1] = hexmap[data & 0x0F];
	return s;
}

string generateMac()
{
	string x;
	for (int i = 0; i < 6; i++)
	{
		x += hexStr(rand());
		if (i != 5)
			x += ":";
	}
	return x;
}

string generateRid()
{
	string x;
	for (int i = 0; i < 16; i++)
	{
		x += hexStr(rand());
	}
	for (auto& c : x) c = toupper(c);
	return x;
}

bool GrowtopiaBot::rep(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

string stripMessage(string msg) {
	regex e("\\x60[a-zA-Z0-9!@#$%^&*()_+\\-=\\[\\]\\{};':\"\\\\|,.<>\\/?]");
	string result = regex_replace(msg, e, "");
	result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
	return result;
}

void delayput()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void delaybreak()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(120));
}

void delaycollect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
uint64_t GetInternalTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void GrowtopiaBot::Collect(int range) {
    for (auto& obj : GrowtopiaBot::floatItem) {
        int rangex = abs((obj.x + 9) / 32 - (localx + 10) / 32);
        int rangey = abs((obj.y + 9) / 32 - (localy + 15) / 32);
        if (rangex <= range && rangey <= range) {
		if (obj.oid == 112){
			if (collectgems){
				    gameupdatepacket_t packet{ 0 };
				    packet.m_type = 11;
				    packet.m_vec_x = obj.x;
				    packet.m_vec_y = obj.y;
				    packet.m_int_data = obj.oid;
				    SendPacketRaw(4, &packet, 56, NULL, peer, 1);
			}else{
			 cout << "cant collect gems..." << endl;	
			}
		}else{
		    gameupdatepacket_t packet{ 0 };
		    packet.m_type = 11;
		    packet.m_vec_x = obj.x;
		    packet.m_vec_y = obj.y;
		    packet.m_int_data = obj.oid;
		    SendPacketRaw(4, &packet, 56, NULL, peer, 1);
		}
            
        }
    }
}


void GrowtopiaBot::PNB(GrowtopiaBot account)
{
    while (enableautofarm)
    {
        if (enableautofarm && !enableautoput && !enableautobreak) { 
            enableautofarm = false; 
        }

        // Put/Place Packet =================================================================================

        if (enableautofarm && enableautoput) // condition put
        {
            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[1])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 2;
                    putpacket.int_y = (int)(localy / 32) - 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[2])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 1;
                    putpacket.int_y = (int)(localy / 32) - 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[3])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32);
                    putpacket.int_y = (int)(localy / 32) - 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[4])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 1;
                    putpacket.int_y = (int)(localy / 32) - 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[5])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 2;
                    putpacket.int_y = (int)(localy / 32) - 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[6])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 2;
                    putpacket.int_y = (int)(localy / 32) - 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[7])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 1;
                    putpacket.int_y = (int)(localy / 32) - 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[8])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32);
                    putpacket.int_y = (int)(localy / 32) - 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[9])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 1;
                    putpacket.int_y = (int)(localy / 32) - 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[10])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 2;
                    putpacket.int_y = (int)(localy / 32) - 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[11])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 2;
                    putpacket.int_y = (int)(localy / 32);
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[12])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 1;
                    putpacket.int_y = (int)(localy / 32);
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[13])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 1;
                    putpacket.int_y = (int)(localy / 32);
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[14])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 2;
                    putpacket.int_y = (int)(localy / 32);
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[15])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 2;
                    putpacket.int_y = (int)(localy / 32) + 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[16])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 1;
                    putpacket.int_y = (int)(localy / 32) + 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[17])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32);
                    putpacket.int_y = (int)(localy / 32) + 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[18])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 1;
                    putpacket.int_y = (int)(localy / 32) + 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[19])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 2;
                    putpacket.int_y = (int)(localy / 32) + 1;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[20])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 2;
                    putpacket.int_y = (int)(localy / 32) + 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[21])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) - 1;
                    putpacket.int_y = (int)(localy / 32) + 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[22])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32);
                    putpacket.int_y = (int)(localy / 32) + 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[23])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 1;
                    putpacket.int_y = (int)(localy / 32) + 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }

            if (enableautofarm && enableautoput)
            {
                if (buttoncolorchange[24])
                {
                    GameUpdatePacket putpacket{ 0 };
                    putpacket.type = PACKET_TILE_CHANGE_REQUEST;
                    putpacket.item_id = itemData;
                    putpacket.int_x = (int)(localx / 32) + 2;
                    putpacket.int_y = (int)(localy / 32) + 2;
                    putpacket.pos_x = (int)(localx);
                    putpacket.pos_y = (int)(localy);
                    account.SendPacketRaw(4, &putpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                    delayput();
                }
            }
        }

        // Punch Packet =================================================================================

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[1]) // Tile 1
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 2);
                punchpacket.punchY = (int)((localy / 32) - 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[2]) // Tile 2
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 1);
                punchpacket.punchY = (int)((localy / 32) - 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[3]) // Tile 3
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32));
                punchpacket.punchY = (int)((localy / 32) - 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[4]) // Tile 4
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 1);
                punchpacket.punchY = (int)((localy / 32) - 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[5]) // Tile 5
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 2);
                punchpacket.punchY = (int)((localy / 32) - 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[6]) // Tile 6
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 2);
                punchpacket.punchY = (int)((localy / 32) - 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[7]) // Tile 7
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 1);
                punchpacket.punchY = (int)((localy / 32) - 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[8]) // Tile 8
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32));
                punchpacket.punchY = (int)((localy / 32) - 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[9]) // Tile 9
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 1);
                punchpacket.punchY = (int)((localy / 32) - 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[10]) // Tile 10
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 2);
                punchpacket.punchY = (int)((localy / 32) - 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[11]) // Tile 11
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 2);
                punchpacket.punchY = (int)((localy / 32));
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[12]) // Tile 12
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 1);
                punchpacket.punchY = (int)((localy / 32));
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[13]) // Tile 13
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 1);
                punchpacket.punchY = (int)((localy / 32));
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[14]) // Tile 14
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 2);
                punchpacket.punchY = (int)((localy / 32));
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[15]) // Tile 15
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 2);
                punchpacket.punchY = (int)((localy / 32) + 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[16]) // Tile 16
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 1);
                punchpacket.punchY = (int)((localy / 32) + 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[17]) // Tile 17
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32));
                punchpacket.punchY = (int)((localy / 32) + 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[18]) // Tile 18
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 1);
                punchpacket.punchY = (int)((localy / 32) + 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[19]) // Tile 19
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 2);
                punchpacket.punchY = (int)((localy / 32) + 1);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[20]) // Tile 20
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 2);
                punchpacket.punchY = (int)((localy / 32) + 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[21]) // Tile 21
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) - 1);
                punchpacket.punchY = (int)((localy / 32) + 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[22]) // Tile 22
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32));
                punchpacket.punchY = (int)((localy / 32) + 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[23]) // Tile 23
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 1);
                punchpacket.punchY = (int)((localy / 32) + 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }

        if (enableautofarm && enableautobreak)
        {
            if (buttoncolorchange[24]) // Tile 24
            {
                TankPacketStruct punchpacket;
                punchpacket.packetType = 3;
                punchpacket.x = (int)(localx);
                punchpacket.y = (int)(localy);
                punchpacket.punchX = (int)((localx / 32) + 2);
                punchpacket.punchY = (int)((localy / 32) + 2);
                punchpacket.value = 18;
                account.SendPacketRaw(4, &punchpacket, 56, 0, account.peer, ENET_PACKET_FLAG_RELIABLE);
                delaybreak();
            }
        }
    }
}

vector<string> string_split(string arg0, string arg1) {

    size_t pos_start = 0, pos_end, delim_len = arg1.length();
    string token;
    vector<string> result;
    result.clear();
    while ((pos_end = arg0.find(arg1, pos_start)) != string::npos) {
        token = arg0.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }
    result.push_back(arg0.substr(pos_start));
    return result;
}

void GrowtopiaBot::updateVersion(std::string text) {
    utils::replace(text, "action|log\nmsg|`4UPDATE REQUIRED!`` : The `$V", "");
    utils::replace(text, "`` update is now available for your device.  Go get it!  You'll need to install it before you can play online.", "");
    gameVersion = text;
    cout << "Version has been updated to " << text << endl;
}

void GrowtopiaBot::onLoginRequested()
{
    http::Request request{ "http://growtopia1.com/growtopia/server_data.php" };
    const auto response = request.send("POST", "version=1&protocol=128", { "Content-Type: application/x-www-form-urlencoded" });
    std::string body = std::string{ response.body.begin(), response.body.end() };
    auto omg = string_split(body, "\n");

    string token;
    if (!login_user && !login_token) {
        token = "";
    }
    else {
        token = "\nuser|" + std::to_string(login_user) + "\ntoken|" + std::to_string(login_token) + "\nUUIDToken|" + login_uuidtoken + "\ndoorID" + DoorID;
    }
    string ver = gameVersion;
    string hash = std::to_string((unsigned int)rand());
    string hash2 = std::to_string((unsigned int)rand());
    string packet = "tankIDName|" + uname + "\ntankIDPass|" + upass + "\nrequestedName|RyoCloud\nf|1\nprotocol|127\ngame_version|" + ver + "\nfz|5367464\nlmode|0\ncbits|0\nplayer_age|18\nGDPR|1\nhash2|" + hash2 + "\n" + omg.at(11) + "\nfhash|-716928004\nrid|" + generateRid() + "\nplatformID|0\ndeviceVersion|0\ncountry|us\nhash|" + hash + "\nmac|" + generateMac() + "\nwk|" + generateRid() + "\nzf|-496303939" + token;
    cout << packet + "\n";
    //cout << "Meta : " + omg.at(11) << endl;
    SendPacket(2, "tankIDName|" + uname + "\ntankIDPass|" + upass + "\nrequestedName|RyoCloud\nf|1\nprotocol|127\ngame_version|" + ver + "\nfz|5367464\nlmode|0\ncbits|0\nplayer_age|18\nGDPR|1\nhash2|" + hash2 + "\n" + omg.at(11) + "\nfhash|-716928004\nrid|" + generateRid() + "\nplatformID|0\ndeviceVersion|0\ncountry|us\nhash|" + hash + "\nmac|" + generateMac() + "\nwk|" + generateRid() + "\nzf|-496303939" + token, peer);
    currentWorld = "";
}

void GrowtopiaBot::packet_type3(string text)
{
	dbgPrint("Some text is here: " + text);
	if (text.find("LOGON ATTEMPTS") != string::npos) {
        statusbot = "Disconnected (Unknown logon fail!)";
        inistatusbot = false;
		//MessageBoxA(NULL, "Unknown logon fail!", "Bot info!", NULL);
	}
	else if (text.find("password is wrong") != string::npos) {
        statusbot = "Disconnected (Password or growid is wrong!)";
        inistatusbot = false;
		//MessageBoxA(NULL, "Password or growid is wrong!", "Bot info!", NULL);
	}
    else if (text.find("Advanced Account Protection") != -1) {
        statusbot = "Disconnected (Advanced account protection!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "Advanced account protection!", "Bot info!", NULL);
    }
    else if (text.find("has been suspended") != -1) {
        statusbot = "Disconnected (Account has been suspended!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "Account has been suspended!", "Bot info!", NULL);
    }
    else if (text.find("this account is currently banned. You will have to wait") != -1) {
        statusbot = "Disconnected (This account is currently banned!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "This account is currently banned!", "Bot info!", NULL);
    }
    else if (text.find("This is a temporary ban") != -1) {
        statusbot = "Disconnected (This device is temporarily banned!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "This device is temporarily banned!", "Bot info!", NULL);
    }
    else if (text.find("View GT Twitter") != -1) {
        statusbot = "Disconnected (Server is under maintenance!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "Server is under maintenance!", "Bot info!", NULL);
    }
    else if (text.find("`4OOPS:") != -1) {
        statusbot = "Disconnected (Too many people logging in at once!)";
        inistatusbot = false;
        //MessageBoxA(NULL, "Too many people logging in at once!", "Bot info!", NULL);
    }
	else if (text.find("UPDATE REQUIRED") != -1) {
        updateVersion(text);
    }
	else if (text.find("action|logon_fail") != string::npos){
        connectClient();
	}
}

void GrowtopiaBot::packet_type6(string packet)
{
	SendPacket(2, "action|enter_game\n", peer);
	enet_host_flush(client);

    PRINTC("Tracking packet: %s\n", packet.c_str());

    if (packet.find("eventName|102_PLAYER.AUTHENTICATION") != -1)
    {
        if (packet.find("Authenticated|1") != -1)
        {
            statusbot = "Connected!";
            inistatusbot = true;
        }
        else
        {
            statusbot = "Disconnected!";
            inistatusbot = false;
        }
    }

    if (packet.find("eventName|100_MOBILE.START") != -1)
    {
        gem = atoi(packet.substr(packet.find("Gems_balance|") + 13, packet.length() - packet.find("Gems_balance|") - 1).c_str());
        level = atoi(packet.substr(packet.find("Level|") + 6, packet.length() - packet.find("Level|") - 1).c_str());
    }

    if (packet.find("eventName|worldexit") != -1)
    {
        currentworld = "In EXIT";
    }

    if (packet.find("eventName|300_WORLD_VISIT") != -1)
    {
        currentworld = packet.substr(packet.find("World_name|") + 13, packet.length() - packet.find("World_name|") - 1);
        currentworld.erase(currentworld.begin() + currentworld.find("\n"), currentworld.end());
    }
}

void GrowtopiaBot::packet_unknown(ENetPacket* packet)
{
	dbgPrint("Got unknown packet type: " + std::to_string(GetMessageTypeFromPacket(packet)));
	dbgPrint("Packet size is " + std::to_string(packet->dataLength));
}

void GrowtopiaBot::OnDialogRequest(string text) {
    // Auto Access
    if (text.find("end_dialog|popup||Continue|") != std::string::npos) {
        if (text.find("acceptlock") != std::string::npos) {
            SendPacket(2, "action|dialog_return\ndialog_name|popup\nnetID|" + to_string(localnetid) + "|\nbuttonClicked|acceptlock", peer);
        }
    }
    else if (text.find("end_dialog|acceptaccess|No|Yes|") != std::string::npos) {
            SendPacket(2, "action|dialog_return\ndialog_name|acceptaccess", peer);
    }
}

void GrowtopiaBot::use() {
	GamePacket pkt{ 0 };
	pkt.type = 7;
	pkt.tile.x = (int)(localx / 32);
	pkt.tile.y = (int)(localy / 32);
	SendPacketRaw(4, &pkt, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

void GrowtopiaBot::move(std::string to, int blocks) {
	if (to == "right") {
		GamePacket pkt{ 0 };
		pkt.type = 0;
		pkt.pos.x = localx + 32 * blocks;
		pkt.pos.y = localy;
		pkt.flags = 32;
		SendPacketRaw(4, &pkt, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		localy = localy;
		localx = localx + 32 * blocks;
	}
	else if (to == "left") {
		GamePacket pkt{ 0 };
		pkt.type = 0;
		pkt.pos.x = localx - 32 * blocks;
		pkt.pos.y = localy;
		pkt.flags = 48;
		SendPacketRaw(4, &pkt, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		localy = localy;
		localx = localx - 32 * blocks;
	}
	else if (to == "down") {
		GamePacket pkt{ 0 };
		pkt.type = 0;
		pkt.pos.x = localx;
		pkt.pos.y = localy + 32 * blocks;
        pkt.flags = 32;
		SendPacketRaw(4, &pkt, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		localy = localy + 32 * blocks;
		localx = localx;
	}
	else if (to == "up") {
		GamePacket pkt{ 0 };
		pkt.type = 0;
		pkt.pos.x = localx;
		pkt.pos.y = localy - 32 * blocks;
        pkt.flags = 32;
		SendPacketRaw(4, &pkt, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
		localy = localy - 32 * blocks;
		localx = localx;
	}
}

void GrowtopiaBot::OnConsoleMessage(string message) 
{
    string strippedMessage = stripMessage(message);
    cout << strippedMessage << endl;

    if (autoAccess) {
        if (message.find("wants to add you to a") != std::string::npos && message.find("Wrench yourself to accept.") != std::string::npos && localnetid != 0) {
            SendPacket(2, "action|wrench\n|netid|" + to_string(localnetid), peer);
        }
    }

	if (automsgg) {
		if (message.find("`` entered, `w") != string::npos) {
			string::size_type loc = message.find("`` entered,", 0);
			SendPacket(2, "action|input\n|text|/msg" + colorstr2(message.substr(3, loc) + msgtextt), peer);
		}
		if (message.find("`` left, `w") != string::npos) {
			string::size_type loc = message.find("`` left,", 0);
			SendPacket(2, "action|input\n|text|/msg" + colorstr2(message.substr(3, loc) + msgtexttt), peer);
		}
	}
}

void GrowtopiaBot::OnPlayPositioned(string sound)
{

}

void GrowtopiaBot::OnSetFreezeState(int state)
{

}

void GrowtopiaBot::OnRemove(string data) // "netID|x\n"
{
	std::stringstream ss(data.c_str());
	std::string to;
	int netID = -1;
	while (std::getline(ss, to, '\n')) {
		string id = to.substr(0, to.find("|"));
		string act = to.substr(to.find("|") + 1, to.length() - to.find("|"));
		if (id == "netID")
		{
			netID = atoi(act.c_str());
		}
		else {
			dbgPrint(id + "!!!!!!!!!!!" + act);
		}
	}
	for (ObjectData& objectData : objects)
	{
		if (objectData.netId == netID)
		{
			objectData.isGone = true;
		}
	}
}

bool Wait(const unsigned long& Time)
{
	clock_t Tick = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Tick < 0) // if clock() fails, it returns -1
		return 0;
	clock_t Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Now < 0)
		return 0;
	while ((Now - Tick) < Time)
	{
		Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
		if (Now < 0)
			return 0;
	}
	return 1;
}

rtvar var2;

void GrowtopiaBot::OnSpawn(string data)
{
	var2 = rtvar::parse(data);

	ObjectData objectData;
	bool actuallyOwner = false;

	   auto name = var2.find(XorStr("name"));
            auto netid = var2.find(XorStr("netID"));
	
			objectData.country = var2.get(XorStr("country"));
		 
			if (stripMessage(var2.get(XorStr("name"))) == ownerUsername) actuallyOwner = true;
			objectData.name = var2.get(XorStr("name"));
		 
			if (actuallyOwner) owner = var2.get_int(XorStr("netID"));
			objectData.netId = var2.get_int(XorStr("netID"));
			objectData.userId = var2.get_int(XorStr("userID"));
		 
		
	auto pos = var2.find(XorStr("posXY"));
                    if (pos && pos->m_values.size() >= 2) {
                        auto x = atoi(pos->m_values[0].c_str());
                        auto y = atoi(pos->m_values[1].c_str());
                        //ply.pos = vector2_t{ float(x), float(y) };
			    objectData.x = x;
			objectData.y = y;
                    }
	
	
	 if (data.find(XorStr("type|local")) != -1) {
                   objectData.isLocal = true;
				localx = objectData.x;
				localy = objectData.y;
				localnetid = objectData.netId;
                localuserid = objectData.userId;
                }
	 if (var2.get(XorStr("mstate")) == "1" || var2.get(XorStr("smstate")) == "1" || var2.get(XorStr("invis"))== "1"){

			objectData.isMod = true;
	 }

	  
	objects.push_back(objectData);

}

void GrowtopiaBot::OnAction(string command)
{
}

void GrowtopiaBot::SetHasGrowID(int state, string name, string password)
{

}

void GrowtopiaBot::SetHasAccountSecured(int state)
{

}

void GrowtopiaBot::OnTalkBubble(int netID, string bubbleText, int type)
{
	cout << bubbleText << endl;
}

void GrowtopiaBot::SetRespawnPos(int respawnPos)
{
	respawnX = respawnPos % 100; // hacky!!! TODO: get from world data (100)
	respawnY = respawnPos / 100; // hacky!!! TODO: get from world data (100)
}

void GrowtopiaBot::OnEmoticonDataChanged(int val1, string emoticons)
{

}

void GrowtopiaBot::OnSetPos(float x, float y)
{
	
}

void GrowtopiaBot::OnAddNotification(string image, string message, string audio, int val1)
{

}

void GrowtopiaBot::AtApplyTileDamage(int x, int y)
{

}

void GrowtopiaBot::AtApplyLock(int x, int y, int itemId)
{
	SendPacket(2, "action|input\n|text|Lock " + std::to_string(itemId) + " applied at X:" + std::to_string(x) + " Y: " + std::to_string(y), peer);
}

void GrowtopiaBot::AtPlayerMoving(PlayerMoving* data)
{
	int object = -1;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i).netId == data->netID)
		{
			object = i;
		}
	}
	if (object != -1)
	{
		objects[object].x = data->x;
		objects[object].y = data->y;
	}
	if (isFollowing && data->netID == owner && data->punchX == -1 && data->punchY == -1 && data->plantingTree == 0)
	{
		if (backwardWalk)
			data->characterState ^= 0x10;
		if ((data->characterState & 0x800) && (data->characterState & 0x100)) {
			SendPacket(2, "action|respawn", peer);
		}
		for (int i = 0; i < objects.size(); i++)
			if (objects.at(i).isLocal) {
				objects.at(i).x = data->x;
				objects.at(i).y = data->y;
			}
		SendPacketRaw(4, packPlayerMoving(data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
}

void GrowtopiaBot::AtAvatarSetIconState(int netID, int state)
{

}

void GrowtopiaBot::WhenConnected()
{

}

void GrowtopiaBot::WhenDisconnected()
{
	userInit();
}

int counter = 0; // 10ms per step

vector<string> explode(const string &delimiter, const string &str)
{
	vector<string> arr;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;//no change

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}

void GrowtopiaBot::userLoop() {



    if (autocollect) {
        if (GetInternalTime() > last_time && range > 0) {
            last_time = GetInternalTime() + 50; // delay 50ms
            Collect(range);
        }
    }

	if (timeFromWorldEnter > 200 && currentWorld != worldName) {
		if (worldName == "" || worldName == "-") {
			timeFromWorldEnter = 0;
		} else {
			SendPacket(3, "action|join_request\nname|" + worldName, peer); // MARRKS
			objects.clear();
		}
		timeFromWorldEnter = 0;
		currentWorld = worldName;
	}
	timeFromWorldEnter++;
	counter++;
	if ((counter % 1800) == 0)
	{
		string name = "";
		float distance = std::numeric_limits<float>::infinity();
		float ownerX;
		float ownerY;
		for (ObjectData x : objects)
		{
			if (x.netId == owner)
			{
				ownerX = x.x;
				ownerY = x.y;
			}
		}
	}
}

void GrowtopiaBot::userInit() {
	connectClient();
	cout << flush;
}

void GrowtopiaBot::respawn()
{
	PlayerMoving data;
	data.characterState = 0x924;
	SendPacket(2, "action|respawn", peer);
	for (int i = 0; i < objects.size(); i++)
		if (objects.at(i).isLocal)
		{
			data.x = objects.at(i).x;
			data.y = objects.at(i).y;
			data.netID = objects.at(i).netId;
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
			break;
		}
}

namespace types {
	typedef	std::chrono::duration<double> elapsed;
	typedef std::chrono::system_clock::time_point time;
}

bool run_at_interval(types::time& timer, double interval) {
	types::time now = std::chrono::system_clock::now();
	types::elapsed elapsed_sec = now - timer;


	if (elapsed_sec.count() >= interval) {
		timer = now;
		return true;
	}
	return false;
}

bool eh;
