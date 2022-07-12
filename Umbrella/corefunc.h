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
#include <cmath>
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
	
	/********* Packet Handle *****************/
	void HandlePacket(BYTE* structPointer, ENetPacket* packets); // handle packet
	
	/********* Process Tank packet funcs  *********/
	void OnState(BYTE* structPointer, ENetPacket* packets); // case 0
	void OnCallFunction(BYTE* structPointer, ENetPacket* packets); // case 1
	void OnUpdateStatus(BYTE* structPointer, ENetPacket* packets); // case 2
	void OnTileChangeRequest(BYTE* structPointer, ENetPacket* packets); // case 3
	void OnSendMapData(BYTE* structPointer, ENetPacket* packets); // case 4
	void OnSendTileUpdateData(BYTE* structPointer, ENetPacket* packets); // case 5
	void OnSendTileUpdateDataMultiple(BYTE* structPointer, ENetPacket* packets); // case 6
	void OnTileActivateRequest(BYTE* structPointer, ENetPacket* packets); // case 7
	void OnTileApplyDamage(BYTE* structPointer, ENetPacket* packets); // case 8
	void OnSendInventoryState(BYTE* structPointer, ENetPacket* packets); // case 9
	void OnItemActivateRequest(BYTE* structPointer, ENetPacket* packets); // case 10
	void OnItemActivateObjectRequest(BYTE* structPointer, ENetPacket* packets);
	void OnSendTileTreeState(BYTE* structPointer, ENetPacket* packets); // case 12
	void OnModifyItemInventory(BYTE* structPointer, ENetPacket* packets); // case 13
	void OnItemChangeObject(BYTE* structPointer, ENetPacket* packets); // case 14
	void OnSendLock(BYTE* structPointer, ENetPacket* packets); // case 15
	void OnSendItemDatabaseData(BYTE* structPointer, ENetPacket* packets); // case 16
	void OnSendParticleEffect(BYTE* structPointer, ENetPacket* packets); // case 17
	void OnSetIconState(BYTE* structPointer, ENetPacket* packets); // case 18
	void OnItemEffect(BYTE* structPointer, ENetPacket* packets); // case 19
	void OnSetCharacterState(BYTE* structPointer, ENetPacket* packets); // case 20
	void OnPingReply(BYTE* structPointer, ENetPacket* packets); // case 21
	void OnPingRequest(BYTE* structPointer, ENetPacket* packets); // case 22
	void OnGotPunched(BYTE* structPointer, ENetPacket* packets); // case 23
	void OnAppCheckResponse(BYTE* structPointer, ENetPacket* packets); // case 24
	void OnAppIntegrityFail(BYTE* structPointer, ENetPacket* packets); // case 25
	void OnDisconnect(BYTE* structPointer, ENetPacket* packets); // case 26
	void OnBattleJoin(BYTE* structPointer, ENetPacket* packets); // case 27
	void OnBattleEven(BYTE* structPointer, ENetPacket* packets); //case 28
	void OnUseDoor(BYTE* structPointer, ENetPacket* packets);// case 29
	void OnSendParental(BYTE* structPointer, ENetPacket* packets); // case 30
	void OnGoneFishin(BYTE* structPointer, ENetPacket* packets); // case 31
	void OnSteam(BYTE* structPointer, ENetPacket* packets); // case 32
	void OnPetBattle(BYTE* structPointer, ENetPacket* packets); // case 33
	void OnNpc(BYTE* structPointer, ENetPacket* packets); // case 34
	void OnSpecial(BYTE* structPointer, ENetPacket* packets); // case 35
	void OnSendParticleEffectV2(BYTE* structPointer, ENetPacket* packets); // case 36
	void OnGameActiveArrowToItem(BYTE* structPointer, ENetPacket* packets); // case 37
	void OnGameSelectTileIndex(BYTE* structPointer, ENetPacket* packets); // case 38
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
	void SendPacket(int a1, string a2, ENetPeer* enetPeer);
	void SendPacketRaw(int a1, void* packetData, size_t packetDataSize, void* a4, ENetPeer* peer, int packetFlag);
	void Disconnect();
	void connectClient();
	void connectClient(string hostName, int port);
	/******************* enet core *********************/



	/*************** sender sutff **************/

	void RequestItemActivate(unsigned int item);
	void SetAndBroadcastIconState(int netID, int state);
	void SendPing();
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



	class EntityComponent {

	};

	BYTE* GetExtendedDataPointerFromTankPacket(BYTE* a1)
	{
		return (BYTE*)((intptr_t)(a1 + 56));
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

	gameupdatepacket_t* get_struct(ENetPacket* packet);

	
	 void packetprint(gameupdatepacket_t* packet){
		 cout << "-------------------------------------" << endl;
		 cout << "m_type : " << packet->m_type << endl;
		 cout << "m_netid : " << packet->m_netid << endl;
		 cout << "m_jump_amount : " << packet->m_jump_amount << endl;
		 cout << "m_player_flags : " << packet->m_player_flags << endl;
		 cout << "m_packet_flags : " << packet->m_packet_flags << endl;
		 cout << "m_struct_flags : " << packet->m_struct_flags << endl;
		 cout << "m_int_data : " << packet->m_int_data << endl;
		 cout << "m_vec_x : " << packet->m_vec_x << endl;
		 cout << "m_vec_y : " << packet->m_vec_y << endl;
		 cout << "m_vec2_x : " << packet->m_vec2_x << endl;
		 cout << "m_vec2_y : " << packet->m_vec2_y << endl;
		 cout << "m_particle_time : " << packet->m_particle_time << endl;
		 cout << "m_state1 : " << packet->m_state1 << endl;
		 cout << "m_state2 : " << packet->m_state2 << endl;
		 cout << "m_data_size : " << packet->m_data_size << endl;
		 cout << "m_data : " << packet->m_data << endl;
		 cout << "-------------------------------------" << endl;

	}
	
	
	void ProcessTankUpdatePacket(BYTE* structPointer, ENetPacket* packets);
	BYTE* GetStructPointerFromTankPacket(ENetPacket* packet);
	void ProcessPacket(ENetEvent* event, ENetPeer* peer);
	void eventLoop();
};


void init() {
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(0);
	}
	atexit(enet_deinitialize);
	srand(time(NULL));
}
