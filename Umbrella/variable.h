#pragma once
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


#include "multibot.h"
#include "Lua_Api.h"

#include <d3d9.h>
#include <tchar.h>
#include <iostream>
#include "xorstr.hpp"
#include "proton/variant.hpp"
//#define CPPHTTPLIB_OPENSSL_SUPPORT
//#include "httplib.h"
#define CURL_STATICLIB
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace std;
using json = nlohmann::json;


std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}
inline bool exists_test(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}




int active_tab = 0;
static int range = 0;

static bool selected[60] = { false };
static bool open = true;
static char usernamebot[120];
static char passwordbot[120];
static char usernamelogin[120];
static char passwordlogin[120];
static char license[120];

static char worldName[60];
char namaFile[40] = "Script.lua";
static char growid[70];

// Auto Spam
static bool autospam;
static char spamtext[500];
float interval = 4;

bool loginpacket = false;
bool autocollect = false;
bool autoreconnect = false;
static int current_item;
static bool selectall;

// Main Tab
bool set = true;
static int speed = 1;
bool follow = false;
bool autoacc = false;
bool asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;

string word = "";
string name = "";
string last;
