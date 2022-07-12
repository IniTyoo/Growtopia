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
#include "SenderSutff.h"
#include "../enet/include/enet.h"
#include "../proton/rtparam.hpp"
#include "../xorstr.hpp"
#include "../HTTPRequest.hpp"


using namespace std;
	void GrowtopiaBot::RequestItemActivate(unsigned int item)
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

	void GrowtopiaBot::SetAndBroadcastIconState(int netID, int state)
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

	void GrowtopiaBot::SendPing()
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