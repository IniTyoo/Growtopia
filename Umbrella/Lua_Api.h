#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include "json.hpp"
#include <string>
#include <windows.h>
#include <direct.h>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>
#include <TlHelp32.h>
#include <tchar.h>.

#include <cmath>
#include <future>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/TextEditor.h"
#include "ItemList.h"

extern "C" {
#include "lua/lauxlib.h"
#include "lua/lua.h"
#include "lua/luaconf.h"
#include "lua/lualib.h"
}



void execute_thread(lua_State* state, std::string text) {
	luaL_dostring(state, text.c_str());
    lua_close(state);
}


// LUA 
static int lua_sendpacket(lua_State* L) {
	if (lua_isstring(L, 2) && lua_isnumber(L, 1)) {
		if (!selectall) {
			bots.at(current_item).SendPacket(lua_tonumber(L, 1), lua_tostring(L, 2), bots.at(current_item).peer);
		}
		
	}
	return 0;
}



void lua_pushbot(lua_State* l, GrowtopiaBot* bot) {
if (!bot) { lua_pushnil(l); return; }
lua_newtable(l);

lua_pushliteral(l, "name");
lua_pushstring(l, bot->uname.c_str());
lua_settable(l, -3);


lua_pushliteral(l, "world");
lua_pushstring(l, bot->currentworld.c_str());
lua_settable(l, -3);

lua_pushliteral(l, "status");
lua_pushstring(l, bot->statusbot.c_str());
lua_settable(l, -3);

lua_pushliteral(l, "x");
lua_pushnumber(l, bot->localx);
lua_settable(l, -3);

lua_pushliteral(l, "y");
lua_pushnumber(l, bot->localy);
lua_settable(l, -3);
} 





int L_GETBOT(lua_State* l) {
int index = luaL_checkinteger(l, 1);
if (index < bots.size() && index > -1) {
GrowtopiaBot* bot = &bots.at(index);
lua_pushbot(l, bot);
} else {
lua_pushnil(l);
}
return 1;
}

// Bot[] getBots()
// int L_GETBOTS(lua_State* l) {
// lua_newtable(l);
// for (int i = 0; i < bots.size(); i++) {
// lua_pushinteger(l, i);
// lua_pushbot(l, &bots.at(i));
// lua_settable(l, -3);
// }
// return 1;
// }

void lua_pushfloatingitem(lua_State* l, int index) {
lua_newtable(l);

lua_pushliteral(l, "PosX");
lua_pushnumber(l, bots.at(current_item).floatItem.at(index).x);
lua_settable(l, -3);
	       
lua_pushliteral(l, "PosY");
lua_pushnumber(l, bots.at(current_item).floatItem.at(index).y);
lua_settable(l, -3);
	       
lua_pushliteral(l, "Id");
lua_pushnumber(l, (int)bots.at(current_item).floatItem.at(index).id);
lua_settable(l, -3);
	       
lua_pushliteral(l, "Flags");
lua_pushnumber(l, (int)bots.at(current_item).floatItem.at(index).flags);
lua_settable(l, -3);
	       
lua_pushliteral(l, "Amount");
lua_pushnumber(l, (int)bots.at(current_item).floatItem.at(index).amount);
lua_settable(l, -3);	  
	       
lua_pushliteral(l, "Oid");
lua_pushnumber(l, (int)bots.at(current_item).floatItem.at(index).oid);
lua_settable(l, -3);

} 


int L_GETFLOATITEMS(lua_State* l) {
lua_newtable(l);
for (int i = 0; i < bots.at(current_item).floatItem.size(); i++) {
lua_pushinteger(l, i);
lua_pushfloatingitem(l, i);
lua_settable(l, -3);
}
return 1;
}


int L_AddBot(lua_State* l){
	if (lua_isstring(l, 1) && lua_isstring(l,2)){
		if(!selectall){
			create(lua_tostring(l, 1), lua_tostring(l, 2));
                	loginpacket = true;	
		}
	}
}
	    
int L_RemoveBot(lua_State* l){
	if(lua_isstring(l,1)){
		for (int i = 0; i < bots.size(); i++) 
            	{
                	if (bots.at(i).uname.c_str() == lua_tostring(l, 1)){
				bots.erase(bots.begin() + i);
                                bots.at(i).WhenDisconnected();
			}
            	}
	}
}

int L_Collect(lua_State* l){
	if(lua_isnumber(l,1)){
		bots.at(current_item).Collect(lua_tonumber(l,1));
	}
}

int L_AutoCollect(lua_State* l){
	if(lua_isboolean(l,1) && lua_isnumber(l,2)){
		bots.at(current_item).autocollect = true;
		bots.at(current_item).range = lua_tonumber(l,2);
		std::thread collecting(autocollecting, bots.at(current_item).range);
                collecting.detach();
	}
}

int L_Connect(lua_State* l){
	bots.at(current_item).userInit();
}
int L_Disconnect(lua_State* l){
	bots.at(current_item).Disconnect();
}

int L_SLEEP(lua_State* l) {
std::this_thread::sleep_for(std::chrono::milliseconds(luaL_checkinteger(l, 1)));
return 1;
}
void executelua(string text){
                if (bots.size() > 0) {
                    lua_State* state = luaL_newstate();
                    luaL_openlibs(state);
                    lua_setglobal(state, "imgui");

                    lua_register(state, "SendPacket", lua_sendpacket);
		    lua_register(state, "AddBot", L_AddBot);
		    lua_register(state, "RemoveBot", L_RemoveBot);
	   	    lua_register(state, "Sleep", L_SLEEP);
		    lua_register(state, "Collect", L_Collect);
		    lua_register(state, "AutoCollect", L_AutoCollect);
		    // Get
		    lua_register(state, "GetFloatItems", L_GETFLOATITEMS);
                    lua_register(state, "GetLocal", L_GETBOT);
			
		    //
                    std::thread thr(execute_thread, state, text);
                    thr.detach();

                }
}


#include <d3d9.h>
#include <tchar.h>
#include <iostream>
#include "globals.h"
#include "xorstr.hpp"
#include "proton/variant.hpp"


