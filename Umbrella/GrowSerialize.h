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
#include "GrowSerialize.h"
#include "enet/include/enet.h"
#include "proton/rtparam.hpp"
#include "xorstr.hpp"
#include "HTTPRequest.hpp"

using namespace std;
  
void GrowtopiaBot::WorldSerialize3(gameupdatepacket_t* packet) {
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

void GrowtopiaBot::SerializeObject4(ENetPacket* packet) {
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


void GrowtopiaBot::UpdateInventory(gameupdatepacket_t* packet) {
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


	void GrowtopiaBot::UpdateObject(gameupdatepacket_t* packet) {
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


	void GrowtopiaBot::decPacket(gameupdatepacket_t* packet) {
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
	
	
