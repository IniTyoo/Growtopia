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
	ENetPeer *peer;
	ENetHost *client;

	int login_user = 0;
	int login_token = 0;

	string currentWorld;
	int timeFromWorldEnter = 0; // in 10mss...

	string gameVersion = "3.93";
	/*********  hidden vars  ********/

	/********** user sutff ***************/
	int owner = -1;
	string ownerUsername;

	string SERVER_HOST = "213.179.209.168";
	int SERVER_PORT = 17257;
	
	int localx=-1;
	int localy=-1;
	int localnetid;
	int localuserid;
	//int worldplayercount=0;

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

	vector<ObjectData> objects;
	vector<string> debug;

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
	bool isFollowing = false;
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
	struct DroppedItem {
		short itemid;
		int x;
		int y;
		BYTE count;
		BYTE flags;
		int uid;
		char padding[0];
	};
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
	void packet_unknown(ENetPacket *packet);
	void move(std::string to, int blocks);
	void OnConsoleMessage(string message);
	void onShowCaptcha(string text);
	void OnDialogRequest(string text);
	void use();
	void solve_captcha(std::string text);
	void OnPlayPositioned(string sound);
	void OnSetFreezeState(int state);
	void OnRemove(string data);
	void OnSpawn(string data);
	void OnAction(string command);
	void SetHasGrowID(int state, string name, string password);
	void SetHasAccountSecured(int state);
	void OnTalkBubble(int netID, string bubbleText, int type);
	void SetRespawnPos(int respawnPos);
	void OnEmoticonDataChanged(int val1, string emoticons);
	void OnSetPos(float x, float y);
	void OnAddNotification(string image, string message, string audio, int val1);
	void AtApplyTileDamage(int x, int y);
	void AtApplyLock(int x, int y, int itemId);
	void AtPlayerMoving(PlayerMoving *data);
	void AtAvatarSetIconState(int netID, int state);
	void WhenConnected();
	void WhenDisconnected();

	void respawn();
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

	void decPacket(gameupdatepacket_t* packet) {
		if (packet) {
			variantlist_t varlist{};
			auto extended = get_extended(packet);
			if (extended) {
				extended += 4;
				varlist.serialize_from_mem(extended);
				cout << "varlist: " << varlist.print() << endl;
				auto debugtext = varlist.print() + "\n\n";
				debug.push_back(debugtext);
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
					connectClient(address, port);
				}
				else if (func == "OnSpawn") {
					auto ctx = varlist[1].get_string();
					if (ctx.find("type|local") != std::string::npos) {
						string net = explode("\n", explode("netID|", ctx)[1])[0];
						string user = explode("\n", explode("userID|", ctx)[1])[0];
						auto gg = explode("|", explode("\n", explode("posXY|", ctx)[1])[0]);//posXY|320|736
						int netid = atoi(net.c_str());
						localuserid = atoi(user.c_str());
						localnetid = netid;localx = atoi(gg[0].c_str());localy = atoi(gg[1].c_str());
						//cout << uname << " Local netid: " << localid << " X: " << localX << " Y: " << localY << endl;
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


	void HandlePacketTileChangeRequest(BYTE* data)
	{
		switch ((*(int*)data) - 8)
		{
		case 0:
			AtApplyTileDamage(*(int*)(data + 44), *(int*)(data + 48));

			break;
		case 4:
			break;
		case 7:
			AtApplyLock(*(int*)(data + 44), *(int*)(data + 48), *(int*)(data + 20));
			break;
		default:
			break;
		}
	}

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

	void sendPunch(int x, int y, int x2, int y2, int net) {
		PlayerMoving data;
		data.packetType = 0x3;
		data.x = x2;
		data.y = y2;
		data.punchX = x;
		data.punchY = y;
		data.netID = net;
		data.plantingTree = 18;
		auto datas = packPlayerMoving(&data);
		SendPacketRaw(4, datas, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}

	void ProcessTankUpdatePacket(float someVal, EntityComponent* entityComponent, BYTE* structPointer, ENetPacket* packets)
	{
		//cout << "Processing tank packet with id of: " << +(*(char*)structPointer) << " Where first byte is " << std::to_string(structPointer[0]) << endl;
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
		case 0xE:
		{
		}
		case 0x23u:
			break;
		case 3:
			break;
		case 4:
		{
			BYTE* worldPtr = GetExtendedDataPointerFromTankPacket(structPointer); // World::LoadFromMem
			world = new WorldStruct;
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
				worldPtr += 4;
			}
			cout << "[" << uname << "] World " + std::to_string(world->XSize) + "x" + std::to_string(world->YSize) + " with name " + world->name << endl;
			//if (world->name.find("TUTORIAL_1") != std::string::npos) SendPacket(2, "action|growid", peer);
			//if (world->name != currentWorld) SendPacket(3, "action|join_request\nname|" + currentWorld, peer);
			//if (world->name == currentWorld) cout << uname << " has been landed in " << currentWorld << endl;
			currentWorld = world->name;
			break;
		}
		case 0: // AvatarPacketReceiver::LerpState
		{
			PlayerMoving* datak = unpackPlayerMoving(structPointer);
			if (datak->packetType == 0 && datak->netID == owner && owner != -1) {
				if (datak->punchX != -1 && datak->punchY != -1) sendPunch(datak->punchX, datak->punchY, datak->x, datak->y, datak->netID);
				SendPacketRaw(4, packPlayerMoving(datak), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
			}
			if (datak->packetType == 0 && datak->netID == localnetid) {
				localx = datak->x;
				localy = datak->y;
			}

			free(datak);
			break;
		}
		case 13:
		{
			
			
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
		userLoop();
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
