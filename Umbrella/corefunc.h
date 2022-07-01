#pragma once
#include "enet/include/enet.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "proton/variant.hpp"
#include "packet.h"
#include "xorstr.hpp"
#include "proton/rtparam.hpp"
#include <regex>
#include "utilsfunc.h"
#include <map>
#include "HTTPRequest.hpp"
using namespace std;


static bool buttoncolorchange[25] = { false };
/*********  hidden vars  ********/
struct vec2 {
	float x;
	float y;
};
struct vec2i {
	int x;
	int y;
};


uint8_t* get_extended(gameupdatepacket_t* packet) {
	return reinterpret_cast<uint8_t*>(&packet->m_data_size);
}
class GrowtopiaBot {
public:
	ENetPeer* peer;
	ENetHost* client;

	int login_user = 0;
	int login_token = 0;
	int lmode = 0;
	string currentWorld;
	int timeFromWorldEnter = 0; // in 10mss...

	string gameVersion = "3.93";
	/*********  hidden vars  ********/

	/********** user sutff ***************/
	int owner = -1;
	string ownerUsername;

	string SERVER_HOST = "213.179.209.168";
	int SERVER_PORT = 17257;

	int localx = -1;
	int localy = -1;
	int localnetid;
	int localuserid;
	int localitem_count;
	int localslot_count;
	int gems;
	
	//int worldplayercount=0;
	
	
	
	
	
	// seturuktur
	struct ObjectData
	{
		int netId = -1;	 // used to interact with stuff in world
		int userId = -1; // growtopia id
		string name = "";
		string country = "";
		string objectType = ""; // "avatar" is player creature
		float x = -1;
		float y = -1;
		bool isGone = false; // set true if character left
		int rectX;			 // collision stuff
		int rectY;			 // collision stuff
		int rectWidth;		 // collision stuff
		int rectHeight;		 // collision stuff
		bool isMod = false;
		bool isLocal = false;
	};

	struct Debug
	{
		string text = "";
	};
	
	struct PlayerMoving {
		int packetType = 0;
		int netID;
		float x;
		float y;
		int characterState;
		int plantingTree;
		float XSpeed;
		float YSpeed;
		int punchX;
		int punchY;
	};
	struct GamePacket {
		char type;
		char objtype;
		char count1;
		char count2;
		int netid;
		int item;
		int flags;
		float float1;
		int int_data;
		vec2 pos;
		vec2 pos2;
		float float2;
		vec2i tile;
		unsigned int data_size;
		unsigned int data;
	};
	struct TankPacketStruct {
#pragma pack (push,1)
		uint8_t packetType = 0;
		uint8_t padding1 = 0, padding2 = 0, padding3 = 0;
		int NetID = 0;
		int secondaryNetID = 0;
		int characterState = 0;
		float padding4 = 0;
		int value = 0;
		float x = 0, y = 0;
		float XSpeed = 0, YSpeed = 0;
		float ptime = 0;
		int punchX = 0, punchY = 0;
		uint32_t extDataSize = 0;
#pragma pack (pop)
	};
	struct InventoryItem {
	    uint16_t id;
	    uint8_t amount;
	};
	
	
	
	struct WorldThingStruct
	{

	};

	

	struct WorldStruct
	{
		int XSize;
		int YSize;
		int tileCount;
		string name;
		__int16* foreground;
		__int16* background;
		WorldThingStruct* specials;
	};
	struct WorldTile {
		int x;
		int y;
		int foreground;
		int background;
	};

	struct World
	{
		int XSize;
		int YSize;
		int tileCount;
		__int16* foreground;
		__int16* background;
	};

	
	struct WorldObject {
		uint16_t id;
		float x;
		float y;
		uint8_t amount;
		uint8_t flags;
		uint32_t oid;
	};

	int last_oid;
	
	
	
	
	// vector
	vector<WorldObject> floatItem;
	std::vector<InventoryItem> inventory;
	vector<ObjectData> objects;
	vector<Debug> debug;
	vector<WorldTile> tiles;
	
	std::map<int, int> GetAllObject() {
	std::map<int, int> ret;
	for (auto obj : floatItem) {
	ret[obj.id] += obj.amount;
	}
	return ret;
	}

	string uname;
	string upass;
	string worldName; // excepted world name

	int gem;
	int level;
	string currentworld = "";
	string statusbot = "";
	bool inistatusbot = false;
	string serveripaddress;
	int serverportaddress;
	int Lmodes = 0;
	string login_uuidtoken;
	string DoorID;

	bool Selected = false;
	bool backwardWalk = false;
	bool autoAccess = false;
	string statusautostartopia;
	string missionstartopia;
	string nukedlogs = "";
	string bansystemlogs = "";
	string donatelogs = "";
	string vendinglogs = "";

	// Autofarm
	bool buttoncolorchange[25] = { false };
	bool enableautofarm = false;
	bool enableautobreak = false;
	bool enableautoput = false;
	bool autocollect = false;
	int itemData = 0;
	int accountblockcount = 0;
	int last_time = 0;
	int range = 0;
	bool collectgems = true;

	// Auto Spam
	char spamtext1[500];
	char spamtext2[500];
	bool autospamm;
	float interval;
	int intervalspam = 4000;

	// Auto MSG
	char msgtextt[500]; //MSG WHEN JOIN
	char msgtexttt[500]; //MSG WHEN LEFT
	bool automsgg;
	float intervalmsg;

	int respawnX;
	int respawnY;
	/********** user sutff ***************/

	/*********** structs declaration *********/
	/*********** structs declaration *********/

	/********* user funcs  *********/
	void userLoop();
	void userInit();
	void PNB(GrowtopiaBot account);
	void updateVersion(std::string text);
	void onLoginRequested();
	bool rep(std::string& str, const std::string& from, const std::string& to);
	void packet_type3(string text);
	void packet_type6(string text);
	void packet_unknown(ENetPacket* packet);
	void move(std::string to, int blocks);
	void use();
	void AtPlayerMoving(PlayerMoving* data);
	void WhenConnected();
	void WhenDisconnected();
	void Wear(int itemid);
	void Drop(int itemid, int count);
	void Trash(int itemid, int count);
	void Collect(int range);
	/********* user funcs  *********/

	/***************    debug stuff   ***************/
	void dbgPrint(string text)
	{
		cout << "[DBG] " + text << endl;
	}
	/***************    debug stuff   ***************/

	GrowtopiaBot(string username, string password)
	{
		this->uname = username;
		this->upass = password;
	}

	/******************* enet core *********************/
	void SendPacket(int a1, string a2, ENetPeer* enetPeer)
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

	void SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag)
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

	// Connect with default value
	void connectClient() {
		connectClient(SERVER_HOST, SERVER_PORT);
	}

	void connectClient(string hostName, int port)
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
	/******************* enet core *********************/



	/*************** sender sutff **************/

	void RequestItemActivate(unsigned int item)
	{
		BYTE* data = new BYTE[56];
		for (int i = 0; i < 56; i++)
		{
			data[i] = 0;
		}
		BYTE ten = 10;
		memcpy(data + 0, &ten, 1);
		memcpy(data + 20, &item, 1);
		SendPacketRaw(4, data, 0x38u, 0, peer, 1);
		free(data);
	}

	void SetAndBroadcastIconState(int netID, int state)
	{
		BYTE* data = new BYTE[56];
		for (int i = 0; i < 56; i++)
		{
			data[i] = 0;
		}
		BYTE eighteen = 18;
		memcpy(data + 0, &eighteen, 1);
		memcpy(data + 4, &netID, 4); // (a1+40)
		memcpy(data + 44, &state, 4);
		SendPacketRaw(4, data, 0x38u, 0, peer, 1);
		free(data);
	}

	void SendPing()
	{
		BYTE* data = new BYTE[56];
		for (int i = 0; i < 56; i++)
		{
			data[i] = 0;
		}
		BYTE twentytwo = 22;
		memcpy(data + 0, &twentytwo, 1);
		SendPacketRaw(4, data, 56, 0, peer, 1);
		free(data);
	}
	/*************** sender sutff **************/


	int GetMessageTypeFromPacket(ENetPacket* packet)
	{
		int result;

		if (packet->dataLength > 3u)
		{
			result = *(packet->data);
		}
		else
		{
			cout << "Bad packet length, ignoring message" << endl;
			result = 0;
		}
		return result;
	}

	char* GetTextPointerFromPacket(ENetPacket* packet)
	{
		char zero = 0;
		memcpy(packet->data + packet->dataLength - 1, &zero, 1);
		return (char*)(packet->data + 4);
	}

	vector<string> explode(const string& delimiter, const string& str)
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
	rtvar var2;
	string stripMessage(string msg) {
	regex e("\\x60[a-zA-Z0-9!@#$%^&*()_+\\-=\\[\\]\\{};':\"\\\\|,.<>\\/?]");
	string result = regex_replace(msg, e, "");
	result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
	return result;
}



string SolveCaptcha(string ID) {
	http::Request request{"http://api.bolwlproxy.com/api/?api=captcha&id=" + ID};
    const auto response = request.send("GET");
    return std::string{response.body.begin(), response.body.end()};
}

vector<string> string_split(string arg0, string arg1) {
	size_t pos_start = 0, pos_end, delim_len = arg1.length();
	string token;
	vector<string> result;
	
	while ((pos_end = arg0.find(arg1, pos_start)) != string::npos) {
		token = arg0.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		result.push_back(token);
	}
	result.push_back(arg0.substr(pos_start));
	return result;
}

	void decPacket(gameupdatepacket_t* packet) {
		if (packet) {
			variantlist_t varlist{};
			auto extended = get_extended(packet);
			if (extended) {
				extended += 4;
				varlist.serialize_from_mem(extended);
				//cout << "varlist: " << varlist.print() << endl;
				auto var1 = varlist[0].get_string();
				auto varx2 = varlist[1].get_string();
				auto var3 = varlist[2].get_string();
				auto var4 = varlist[3].get_string();
				auto var5 = varlist[4].get_string();
				Debug debag;
				debag.text = varlist.print().c_str();
				debug.push_back(debag);
				auto func = varlist[0].get_string();
				if (func == "OnSendToServer") {
					auto port = varlist[1].get_uint32();
					login_user = varlist[3].get_uint32();
					login_token = varlist[2].get_uint32();
					auto str = varlist[4].get_string();
					DoorID = str.substr(16, 1);
					login_uuidtoken = str.substr(18, 32);
					auto address = str.substr(0, 15);
					serveripaddress = address;
					serverportaddress = port;
					lmode = varlist[5].get_int32();
					connectClient(address, port);
				}
				else if (func == "onShowCaptcha") {
					auto ctx = varlist[1].get_string();
				}
				else if (func == "OnRequestWorldSelectMenu") {
                			auto ctx = varlist[1].get_string();
                			currentworld = "In EXIT";
            			}
				else if (func == "OnSetPos") {
					auto ctx = varlist[1].get_string();
					localx = varlist[1].get_vector2().m_x;
					localy = varlist[1].get_vector2().m_y;
				}
				else if (func == "OnDialogRequest") {
					auto ctx = varlist[1].get_string();
					// Auto Access
					if (ctx.find("end_dialog|popup||Continue|") != std::string::npos) {
						if (ctx.find("acceptlock") != std::string::npos) {
							SendPacket(2, "action|dialog_return\ndialog_name|popup\nnetID|" + to_string(localnetid) + "|\nbuttonClicked|acceptlock", peer);
						}
					}
					else if (ctx.find("end_dialog|acceptaccess|No|Yes|") != std::string::npos) {
						SendPacket(2, "action|dialog_return\ndialog_name|acceptaccess", peer);
					}
				}
				else if (func == "onShowCaptcha") {
	    			auto ctx = varlist[1].get_string();
	    			auto Kepo = string_split(ctx, "|");
	    			auto CaptchaID = string_split(string_split(Kepo.at(1), "/").at(3), "-");
	    			string RealCaptchaID = CaptchaID.at(0);
	    			for (int i = 1; i < CaptchaID.size() - 1; i++) {
	    				RealCaptchaID += "-" + CaptchaID.at(i);
	    				}
	    				string CaptchaIDs = Kepo.at(4);
	    			SendPacket(2, "action|dialog_return\ndialog_name|puzzle_captcha_submit\ncaptcha_answer|" + SolveCaptcha(RealCaptchaID) + "|CaptchaID|" + CaptchaIDs, peer);
	    			}
				else if (func == "OnConsoleMessage") {
					auto ctx = varlist[1].get_string();
					if (autoAccess) {
						if (ctx.find("wants to add you to a") != std::string::npos && ctx.find("Wrench yourself to accept.") != std::string::npos && localnetid != 0) {
							SendPacket(2, "action|wrench\n|netid|" + to_string(localnetid), peer);
						}
					}
					if (automsgg) {
						if (ctx.find("`` entered, `w") != string::npos) {
							string::size_type loc = ctx.find("`` entered,", 0);
							SendPacket(2, "action|input\n|text|/msg" + colorstr2(ctx.substr(3, loc) + msgtextt), peer);
						}
						if (ctx.find("`` left, `w") != string::npos) {
							string::size_type loc = ctx.find("`` left,", 0);
							SendPacket(2, "action|input\n|text|/msg" + colorstr2(ctx.substr(3, loc) + msgtexttt), peer);
						}
					}
				}
				else if (func == "OnSpawn") {
					auto data = varlist[1].get_string();
					std::stringstream ss(data.c_str());
					std::string to;
					cout << data;
					ObjectData objectData;
					bool actuallyOwner = false;

					while (std::getline(ss, to, '\n')) {
						string id = to.substr(0, to.find("|"));
						string act = to.substr(to.find("|") + 1, to.length() - to.find("|") - 1);
						if (id == "country")
						{
							objectData.country = act;
						}
						else if (id == "name")
						{
							if (stripMessage(act) == ownerUsername) actuallyOwner = true;
							objectData.name = act;
						}
						else if (id == "netID")
						{
							if (actuallyOwner) owner = atoi(act.c_str());
							objectData.netId = atoi(act.c_str());
						}
						else if (id == "userID")
						{
							objectData.userId = atoi(act.c_str());
						}
						else if (id == "posXY")
						{
							int x = atoi(act.substr(0, to.find("|")).c_str());
							int y = atoi(act.substr(act.find("|") + 1, act.length() - act.find("|") - 1).c_str());
							objectData.x = x;
							objectData.y = y;
							localnetid = objectData.netId;
							localuserid = objectData.userId;
						}
						else if (id == "type")
						{
							if (act == "local")
								objectData.isLocal = true;
						}
						else if (act != "0" && (id == "invis" || id == "mstate" || id == "smstate"))
						{
							cout << "Some fishy boy is here: " << objectData.name << "; " << objectData.country << "; " << objectData.userId << "; " << objectData.netId << "; " << endl;
							objectData.isMod = true;
						}
					}
					
					objects.push_back(objectData);


					/*
					struct ObjectData
				{
					int netId = -1;	 // used to interact with stuff in world
					int userId = -1; // growtopia id
					string name = "";
					string country = "";
					string objectType = ""; // "avatar" is player creature
					float x = -1;
					float y = -1;
					bool isGone = false; // set true if character left
					int rectX;			 // collision stuff
					int rectY;			 // collision stuff
					int rectWidth;		 // collision stuff
					int rectHeight;		 // collision stuff
					bool isMod = false;
					bool isLocal = false;
				};*/
				}
				else if (func == "OnRemove") {
					auto ctx = varlist[1].get_string();
					std::stringstream ss(ctx.c_str());
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
			}
		}
	}

	class EntityComponent {

	};

	BYTE* GetExtendedDataPointerFromTankPacket(BYTE* a1)
	{
		return (BYTE*)((intptr_t)(a1 + 56));
	}
	
	void UpdateObject(gameupdatepacket_t* packet) {
		// netid -1 > new object
		if (packet->m_player_flags == -1) {
			WorldObject obj;
			obj.id = packet->m_int_data;
			obj.x = packet->m_vec_x;
			obj.y = packet->m_vec_y;
			obj.amount = (uint8_t)packet->m_struct_flags;
			obj.flags = packet->m_netid;
			obj.oid = ++last_oid;

			cout << "Object ID:" << obj.id << endl;
			cout << "Object Amount:" << (int)obj.amount << endl;
			cout << "Object Oid:" << obj.oid << endl;
			cout << "Object PosX:" << obj.x << endl;
			cout << "Object PosY:" << obj.y << endl;

			floatItem.push_back(obj);
		}

		// netid -3 > update object amount
		else if (packet->m_player_flags == -3) {
			for (auto& obj : floatItem) {
				if (obj.id == packet->m_int_data && obj.x == packet->m_vec_x && obj.y == packet->m_vec_y) {
					obj.amount = (uint8_t)packet->m_struct_flags;
					cout << "Object ID:" << obj.id << endl;
					cout << "Object Amount:" << (int)obj.amount << endl;
					cout << "Object Oid:" << obj.oid << endl;
					cout << "Object PosX:" << obj.x << endl;
					cout << "Object PosY:" << obj.y << endl;
					break;
				}
			}
		}

		// other number, erase object
		else {
            for (int i = 0; i < floatItem.size(); i++) {
                if (floatItem[i].oid == packet->m_int_data) {
                    
                    // add to inventory if netid same like local netid
                    if (packet->m_player_flags == localnetid) { // netid = local player netid
                        if (floatItem[i].id == 112) {
                            gems += floatItem[i].amount; // gems
                        } else {
                            bool added = false;
                            for (auto& item : inventory) { // inventory = vector for inventory
                                if (item.id == floatItem[i].id) {
                                    int temp = item.amount + floatItem[i].amount;
                                    if (temp > 200)
                                        item.amount = 200;
                                    else
                                        item.amount = temp;
                                    added = true;
                                    break;
                                }
                            }
                            if (!added) {
                                InventoryItem item;
                                item.id = floatItem[i].id;
                                item.amount = floatItem[i].amount;
                                inventory.push_back(item); // inventory
                            }
                        }
                    }
                    
                    // erase
                    floatItem.erase(floatItem.begin() + i);
                    break;
                }
            }
        }
    }
	void SerializeObject(ENetPacket* packet) {
		uint8_t* extended = packet->data + packet->dataLength;
		extended -= 17; // stable
		int estimate = *(int*)(extended);
		for (int i = 0; i < estimate + 1; i++) {
			if (*(uint8_t*)(extended - i * 16 - 2) == 0) {
				last_oid = *(int*)(extended - i * 16);
				std::cout << "Last object id: " << last_oid << std::endl;
				break;
			}
			WorldObject obj;
			obj.id = *(uint16_t*)(extended - i * 16 - 12);
			memcpy(&obj.x, extended - i * 16 - 10, 4);
			memcpy(&obj.y, extended - i * 16 - 6, 4);
			obj.amount = *(uint8_t*)(extended - i * 16 - 2);
			obj.flags = *(uint8_t*)(extended - i * 16 - 1);
			obj.oid = *(uint32_t*)(extended - i * 16);
			cout << "Object ID:" << obj.id << endl;
			cout << "Object Amount:" << (int)obj.amount << endl;
			cout << "Object Oid:" << obj.oid << endl;
			cout << "Object PosX:" << obj.x << endl;
			cout << "Object PosY:" << obj.y << endl;
			floatItem.push_back(obj);
		}
	}
	
	void SerializeInventory(ENetPacket* packet) {
        uint8_t* extended = packet->data + 60;
        extended += 5;

        uint8_t size = *(extended);
        for (uint8_t i = 0; i < size; i++) {
            InventoryItem item;
            extended += 2;
            item.id = *(short*)(extended);
            extended += 2;
            item.amount = *(extended);
            inventory.push_back(item);
            //std::cout << "Added item: " << item.id << "|" << item.amount << std::endl;
        }
    }
	
	void UpdateInventory(gameupdatepacket_t* packet) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].id == packet->m_int_data) {
                int temp = inventory[i].amount - packet->m_jump_amount;
                if (temp < 1)
                    inventory.erase(inventory.begin() + i);
                else
                    inventory[i].amount = temp;
                break;
            }
        }
    }
	void UpdateInventory3(gameupdatepacket_t* packet) {
        if (packet->m_player_flags == localnetid) {
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].id == packet->m_int_data) {
                    inventory[i].amount --;
                    if (inventory[i].amount < 1)
                        inventory.erase(inventory.begin() + i);
                    break;
                }
            }
        }
    }
		

	BYTE* packPlayerMoving(PlayerMoving* dataStruct)
	{
		try
		{
			BYTE* data = new BYTE[56];
			for (int i = 0; i < 56; i++)
			{
				data[i] = 0;
			}
			memcpy(data, &dataStruct->packetType, 4);
			memcpy(data + 4, &dataStruct->netID, 4);
			memcpy(data + 12, &dataStruct->characterState, 4);
			memcpy(data + 20, &dataStruct->plantingTree, 4);
			memcpy(data + 24, &dataStruct->x, 4);
			memcpy(data + 28, &dataStruct->y, 4);
			memcpy(data + 32, &dataStruct->XSpeed, 4);
			memcpy(data + 36, &dataStruct->YSpeed, 4);
			memcpy(data + 44, &dataStruct->punchX, 4);
			memcpy(data + 48, &dataStruct->punchY, 4);
			return data;
		}
		catch (std::exception) {
			return NULL;
		}
	}
	PlayerMoving* unpackPlayerMoving(BYTE* data)
	{
		try
		{
			PlayerMoving* dataStruct = new PlayerMoving;
			memcpy(&dataStruct->packetType, data, 4);
			memcpy(&dataStruct->netID, data + 4, 4);
			memcpy(&dataStruct->characterState, data + 12, 4);
			memcpy(&dataStruct->plantingTree, data + 20, 4);
			memcpy(&dataStruct->x, data + 24, 4);
			memcpy(&dataStruct->y, data + 28, 4);
			memcpy(&dataStruct->XSpeed, data + 32, 4);
			memcpy(&dataStruct->YSpeed, data + 36, 4);
			memcpy(&dataStruct->punchX, data + 44, 4);
			memcpy(&dataStruct->punchY, data + 48, 4);
			return dataStruct;
		}
		catch (...) {
			return NULL;
		}
	}

	WorldStruct* world = NULL;

	gameupdatepacket_t* get_struct(ENetPacket* packet) {
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

	void ProcessTankUpdatePacket(float someVal, EntityComponent* entityComponent, BYTE* structPointer, ENetPacket* packets)
	{
		cout << "Processing tank packet with id of: " << +(*(char*)structPointer) << " Where first byte is " << std::to_string(structPointer[0]) << endl;
		auto ptype = *(char*)structPointer;
		switch (*(char*)structPointer)
		{
		case 1:
		{
			try {
				auto packet = get_struct(packets);
				decPacket(packet);
				//SerializeFromMem(GetExtendedDataPointerFromTankPacket(structPointer), *(int*)(structPointer + 52), 0, *(int*)(structPointer + 4));				
			}
			catch (int e)
			{

			}
			break;
		}
		case 7: {
			PlayerMoving* datak = unpackPlayerMoving(structPointer);
			cout << "Type 7: " << datak->netID << endl;
			break;
		}
		case 0x10:
		{
			BYTE* itemsData = GetExtendedDataPointerFromTankPacket(structPointer);
			__int16 val1 = *(__int16*)itemsData;
			int itemsCount = *(int*)(itemsData + 2);
			break;
		}
		case 13:
		{
			UpdateInventory(get_struct(packets));
			break;
		}
		case 0x16:
		{
			PlayerMoving* datak = unpackPlayerMoving(structPointer);
			datak->packetType = 21;
			SendPacketRaw(4, packPlayerMoving(datak), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
			break;
			// SendPacketRaw(4, &v205, 0x38u, 0, peer, 1);
		}
		break;
		case 0x12:
		{
			break;
		}
		case 0x14:
		{
			break;
		}
		case 0xC:
		{
			string x = std::to_string(*(int*)(structPointer + 44));
			string y = std::to_string(*(int*)(structPointer + 48));
			//SendPacket(2, "action|input\n|text|x: " + x + ", y: " + y, peer);
			break;
		}
		case 0xE: // 14
		{
			UpdateObject(get_struct(packets));
			break;
		}
		case 0x23u:
			break;
		case 3:
		{	
			cout << get_struct(packets) << endl;
			UpdateInventory3(get_struct(packets));
			break;
		}
		case 9:
		{
			inventory.clear();
			SerializeInventory(packets);
			break;
		}
		case 4:
		{
			tiles.clear();
			floatItem.clear();
			last_oid = 0;
			SerializeObject(packets);
			tile.clear();
			BYTE* worldPtr = GetExtendedDataPointerFromTankPacket(structPointer); // World::LoadFromMem
			world = new WorldStruct;
			World wrld;
			worldPtr += 6;
			__int16 strlen = *(__int16*)worldPtr;
			worldPtr += 2;
			world->name = "";
			for (int i = 0; i < strlen; i++)
			{
				world->name += worldPtr[0];
				worldPtr++;
			}
			world->XSize = *(int*)worldPtr;
			worldPtr += 4;
			world->YSize = *(int*)worldPtr;
			worldPtr += 4;
			world->tileCount = *(int*)worldPtr;
			worldPtr += 4;
			world->foreground = (__int16*)malloc(world->tileCount * sizeof(__int16));
			world->background = (__int16*)malloc(world->tileCount * sizeof(__int16));
			wrld.XSize = world->XSize;
			wrld.YSize = world->YSize;

			for (int i = 0; i < world->tileCount; i++)
			{
				world->foreground[i] = *(__int16*)worldPtr;
				//if (i<100)
				//cout << std::hex << *(__int16_t*)worldPtr << " ";
				worldPtr += 2;
				world->background[i] = *(__int16*)worldPtr;
				worldPtr += 2;
				if (*(BYTE*)worldPtr == 0xae) // locked area
				{
					worldPtr += 2; //10  // 0 4 6 8 10
				}
				else if (world->foreground[i] == 0xca) // small lock
				{
					worldPtr += 10;
				}
				else if (world->foreground[i] == 242) // world lock
				{
					worldPtr += 30; // 12
				}
				else if (world->foreground[i] == 4802) // crown lock?
				{
					worldPtr += 14;
				}
				else if (world->foreground[i] == 6) // main door
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				}
				else if (world->foreground[i] == 20) // sign
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4 + 3;
				}
				else if (world->foreground[i] == 28) // danger sign // TODO
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4 + 3;
				}
				else if (world->foreground[i] == 1682) // gateway to adventure
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				}
				else if (world->foreground[i] == 858) // screen door
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				}
				else if (world->foreground[i] == 382) // time space rupture
				{
					worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				}
				else if (world->foreground[i] == 546) worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				else if (world->foreground[i] == 12) worldPtr += (*(__int16*)(worldPtr + 5)) + 4;
				else if (world->foreground[i] == 3808) worldPtr += 1;
				else if (world->foreground[i] == 3804) // challenge timer
				{
					worldPtr += 1;
				}
				else if (world->foreground[i] == 3806) // challenge start flag
				{
					worldPtr += 1;
				}
				else if (world->foreground[i] == 658) // bulletin board
				{
					worldPtr += 7;
				}
				else if (world->foreground[i] == 1684) // path marker
				{
					worldPtr += 7;
				}
				else if (world->foreground[i] == 3760) // data bedrock
				{
					worldPtr += 2;
				}
				else if (world->foreground[i] == 1420) // mannequin
				{
					worldPtr += 26;
				}
				else if (world->foreground[i] % 2) { // seeds
					worldPtr += 6;
				}
				else if (0 != *(BYTE*)worldPtr)
				{

				}
				/*
				struct WorldTile {
		int x;
		int y;
		__int16* foreground;
		__int16* background;
	};
	*/
				if (i < 100){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 1 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 1;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				if (i < 200){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 2 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 2;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				if (i < 300){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 3 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 3;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				if (i < 400){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 4 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 4;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				if (i =< 500){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 5 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 5;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				if (i < 600){
				cout <<"World fg:" << world->foreground[i] << " | bg: " << world->background[i] << " | POS X:" << i << " | Y:" << 6 << endl;
					WorldTile tile;
					tile.x  = i;
					tile.y = 6;
					tile.foreground = (int)world->foreground[i];
					tile.background = (int)world->background[i];
					tiles.push_back(tile);
				}
				worldPtr += 4;
				//tile.push_back(wrld);
			}
			cout << "[" << uname << "] World " + std::to_string(world->XSize) + "x" + std::to_string(world->YSize) + " with name " + world->name << endl;
			//if (world->name.find("TUTORIAL_1") != std::string::npos) SendPacket(2, "action|growid", peer);
			//if (world->name != currentWorld) SendPacket(3, "action|join_request\nname|" + currentWorld, peer);
			//if (world->name == currentWorld) cout << uname << " has been landed in " << currentWorld << endl;
			if (world->name == "EXIT") objects.clear();
			currentWorld = world->name;
			break;
		}
		case 0: // AvatarPacketReceiver::LerpState
		{
			PlayerMoving* datak = unpackPlayerMoving(structPointer);
			AtPlayerMoving(datak);
			free(datak);
			break;
		}
		default:
			break;
		}

	}

	BYTE* GetStructPointerFromTankPacket(ENetPacket* packet)
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

	void ProcessPacket(ENetEvent* event, ENetPeer* peer)
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
				ProcessTankUpdatePacket(0, NULL, tankUpdatePacket, event->packet);
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

	void eventLoop()
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
};


void init() {
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(0);
	}
	atexit(enet_deinitialize);
	srand(time(NULL));
}
