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


#include <d3d9.h>
#include <tchar.h>
#include <iostream>
#include "globals.h"
#include "xorstr.hpp"
#include "proton/variant.hpp"


#include "auth.hpp"
#include "skStr.h"
#define CURL_STATICLIB
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace KeyAuth;

std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
std::string namex = "payung"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "MCbJ0h8d3p"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "2e013a6ac7c57740f8ad0ecab08f7c7bf0af0d0aad7b5812e18fe082baf41b65"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://umberella-server.000webhostapp.com/api/1.1/"; // change if you're self-hosting
api KeyAuthApp(namex, ownerid, secret, version, url, sslPin);

using namespace std;
using json = nlohmann::json;

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
bool asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = false;

string word = "";
string name = "";
string last;

vector<GrowtopiaBot> bots;
GrowtopiaBot create(string username, string password) {
    GrowtopiaBot bot = { username, password };
    http::Request request{ "http://growtopia2.com/growtopia/server_data.php" };
    const auto response = request.send("POST", "version=1&protocol=128", { "Content-Type: application/x-www-form-urlencoded" });
    rtvar var = rtvar::parse({ response.body.begin(), response.body.end() });
    var.serialize();
    if (var.find("server")) {
        bot.SERVER_HOST = var.get("server");
        bot.SERVER_PORT = std::stoi(var.get("port"));
    }
    cout << "Parsing port and ip is done. port is " << to_string(bot.SERVER_PORT).c_str() << " and ip is " << bot.SERVER_HOST << endl;
    bot.userInit();
    bots.push_back(bot);
    return bot;
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
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

static int lua_moveright(lua_State* L) {
	if (lua_isnumber(L, 1)) {
		if (!selectall) {
			bots.at(current_item).move(XorStr("right"), lua_tonumber(L, 1));
		}
		
	}else{
		if (!selectall) {
			bots.at(current_item).move(XorStr("right"), 1);
		}	
	}
	return 0;
}

static int lua_moveleft(lua_State* L) {
	if (lua_isnumber(L, 1)) {
		if (!selectall) {
			bots.at(current_item).move(XorStr("left"), lua_tonumber(L, 1));
		}
		
	}else{
		if (!selectall) {
			bots.at(current_item).move(XorStr("left"), 1);
		}	
	}
	return 0;
}

static int lua_movedown(lua_State* L) {
	if (lua_isnumber(L, 1)) {
		if (!selectall) {
			bots.at(current_item).move(XorStr("down"), lua_tonumber(L, 1));
		}
		
	}else{
		if (!selectall) {
			bots.at(current_item).move(XorStr("down"), 1);
		}	
	}
	return 0;
}
static int lua_moveup(lua_State* L) {
	if (lua_isnumber(L, 1)) {
		if (!selectall) {
			bots.at(current_item).move(XorStr("up"), lua_tonumber(L, 1));
		}
		
	}else{
		if (!selectall) {
			bots.at(current_item).move(XorStr("up"), 1);
		}	
	}
	return 0;
}


static int lua_getbot(lua_State* L) {
				    lua_newtable(L);
					lua_pushliteral(L, "x"); // assign table.x
					lua_pushnumber(L, bots.at(current_item).localx); // misal value 1000
					lua_settable(L, -3); // wajib -3
					    
					lua_pushliteral(L, "y"); // assign table.x
					lua_pushnumber(L, bots.at(current_item).localy); // misal value 1000
					lua_settable(L, -3); // wajib -3

					lua_pushliteral(L, "world"); // assign table.x
					lua_pushstring(L, bots.at(current_item).currentworld.c_str()); // misal value 1000
					lua_settable(L, -3); // wajib -3
					    
					lua_pushliteral(L, "status"); // assign table.x
					lua_pushstring(L, bots.at(current_item).statusbot.c_str()); // misal value 1000
					lua_settable(L, -3); // wajib -3
					
					    
					lua_pushliteral(L, "name"); // assign table.x
					lua_pushstring(L, bots.at(current_item).uname.c_str()); // misal value 1000
					lua_settable(L, -3); // wajib -3
					    //.statusbot.c_str()

					//...
					return 1;
					}

void executelua(string text){
                if (bots.size() > 0) {
                    lua_State* state = luaL_newstate();
                    luaL_openlibs(state);

                    //lua_newtable(state);
                    lua_setglobal(state, "imgui");

                    lua_register(state, "SendPacket", lua_sendpacket);
                    lua_register(state, "GetBot", lua_getbot);
		    lua_register(state, "MoveRight", lua_moveright);
		    lua_register(state, "MoveLeft", lua_moveleft);
		    lua_register(state, "MoveUp", lua_moveup);
		    lua_register(state, "MoveDown", lua_movedown);
                    auto script = "local clock = os.clock\nfunction sleep(n)  -- ms kasih .\nlocal t0 = clock()\nwhile clock() - t0 <= n do end\nend\n\n\n" + text;
                    std::thread thr(execute_thread, state, script);
                    thr.detach();

                }
}

inline bool exists_test(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}


void spamthread(std::string text1)
{
    using namespace std::literals::chrono_literals;
    for (auto& bot : bots)
    {
        while (bot.autospamm)
        {
            for (auto& bot : bots)
            {
                bot.SendPacket(2, "action|input\n|text|" + text1, bot.peer);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(bot.intervalspam));
        }
    }
}

void autocollecting(int range)
{
    using namespace std::literals::chrono_literals;
    for (auto& bot : bots)
    {
        while (bot.autocollect)
        {
            for (auto& bot : bots)
            {
                bot.Collect(bot.range);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}



static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled(XorStr("(?)").c_str());
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int main()
{
    SetConsoleTitleA(skCrypt("Loader"));
    std::cout << skCrypt("\n\n Connecting..");
    KeyAuthApp.init();
    if (!KeyAuthApp.data.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
        Sleep(1500);
        exit(0);
    }




    /*
    KeyAuthApp.web_login();
    std::cout << "\n Waiting for button to be clicked";
    KeyAuthApp.button("close");
    */

    /*
    for (std::string subs : KeyAuthApp.data.subscriptions)
    {
        if (subs == "default")
        {
            std::cout << skCrypt("\n User has subscription with name: default");
        }
    }
    */

    /*
    // download file, change file.exe to whatever you want.
    // remember, certain paths like windows folder will require you to turn on auto run as admin https://stackoverflow.com/a/19617989
    std::vector<std::uint8_t> bytes = KeyAuthApp.download("167212");
    std::ofstream file("file.exe", std::ios_base::out | std::ios_base::binary);
    file.write((char*)bytes.data(), bytes.size());
    file.close();
    */

    // KeyAuthApp.setvar("discord", "test#0001"); // set the variable 'discord' to 'test#0001'
    // std::cout << "\n\n User variable data: " + KeyAuthApp.getvar("discord"); // display the user variable witn name 'discord'

    // let's say you want to send request to https://keyauth.win/api/seller/?sellerkey=f43795eb89d6060b74cdfc56978155ef&type=black&ip=1.1.1.1&hwid=abc
    // but doing that from inside the loader is a bad idea as the link could get leaked.
    // Instead, you should create a webhook with the https://keyauth.win/api/seller/?sellerkey=f43795eb89d6060b74cdfc56978155ef part as the URL
    // then in your loader, put the rest of the link (the other paramaters) in your loader. And then it will send request from KeyAuth server and return response in string resp

    // you have to encode the & sign with %26
    // std::string resp = KeyAuthApp.webhook("P5NHesuZyf", "%26type=black%26ip=1.1.1.1%26hwid=abc");
    // std::cout << "\n Response recieved from webhook request: " + resp;

    // KeyAuthApp.log("user logged in"); // send event to logs. if you set discord webhook in app settings, it will send there too
    // KeyAuthApp.ban(); // ban the current user, must be logged in

    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("UMBRELLA"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("UMBRELLA"), WS_OVERLAPPEDWINDOW, 0, 0, 50, 50, NULL, NULL, wc.hInstance, NULL);

    // Hide console window
    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    // Init Direct3d
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_HIDE);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    ImFont* font;
    font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 16);

    auto lang = TextEditor::LanguageDefinition::Lua();

    static TextEditor editor;
    static TextEditor editor2;

    editor.SetLanguageDefinition(lang);
    editor.SetPalette(TextEditor::GetDarkPalette());

    editor2.SetLanguageDefinition(lang);
    editor2.SetPalette(TextEditor::GetDarkPalette());

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 4.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);


    bool done = false;

    GrowtopiaBot bot = {
    usernamebot , passwordbot
    };

    init();
    while (!done)
    {
        if (loginpacket)
        {
            for (int i = 0; i < bots.size(); i++) 
            {
                bots.at(i).eventLoop();
                bots.at(i).userLoop();
            }
        }

        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            //auto nama = KeyAuthApp.data.username;
            auto window_title = "Umbrella BETA 1.0 By Dr. Aseppp Of Beban#8307";//+ KeyAuthApp.data.username;
            ImVec2 window_size{ 650, 415 };

            DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
            if (globals.active)
            {
                ImGui::SetNextWindowSize(window_size);
                ImGui::SetNextWindowBgAlpha(1.0f);
                ImGui::StyleColorsGreenBlue();
                ImGui::PushFont(font);
                {
                    ImGui::Begin(window_title, &globals.active, window_flags);
                    if (asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd == false) {
                        //std::cout << skCrypt("\n\n Connecting..");
                       // KeyAuthApp.init();
                        ImGui::BeginTabBar("##Tahggb 1");
                        if (ImGui::BeginTabItem("Login"))
                        {
                            //string usernamelogin;
                            ImGui::InputTextWithHint("##worldsd3", "Username", usernamelogin, sizeof(usernamelogin), 0);
                            ImGui::InputTextWithHint(XorStr("##wosdrld2").c_str(), "Password", passwordlogin, sizeof(passwordlogin), ImGuiInputTextFlags_Password);
                            if (ImGui::Button("Login", ImVec2(sizeof(usernamelogin), 20)))
                            {
                                //KeyAuthApp.login(usernamelogin, passwordlogin);
                               // asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;
                                KeyAuthApp.login(usernamelogin, passwordlogin);
                                if (!KeyAuthApp.data.success)
                                {
                                    std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                                    Sleep(1500);
                                    ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                                   // ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
                                }
                                else {
                                    cout << "Sukses" << endl;
                                    asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;
                                    ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                                    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
                                }
                                //break;
                            }
                            //ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Register"))
                        {
                            //string usernamelogin;
                            ImGui::InputTextWithHint("##wosdsdrsdsdldsd3", "License", license, sizeof(license), 0);
                            ImGui::InputTextWithHint("##worsdsdldsd3", "Username", usernamelogin, sizeof(usernamelogin), 0);
                            ImGui::InputTextWithHint(XorStr("##wosdrld2").c_str(), "Password", passwordlogin, sizeof(passwordlogin), ImGuiInputTextFlags_Password);
                            if (ImGui::Button("Register", ImVec2(sizeof(usernamelogin), 20)))
                            {
                                KeyAuthApp.regstr(usernamelogin, passwordlogin, license);
                                if (!KeyAuthApp.data.success)
                                {
                                    std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                                    Sleep(1500);
                                    ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                                }
                                else {
                                    cout << "Sukses" << endl;
                                    asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;
                                    ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                                   // ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
                                }
                                //asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;
                                //break;

                            }/*bool success;
			std::string message;*/
                            //ImGui::Text("Status: %s", KeyAuthApp.data.message + " | " + KeyAuthApp.data.success);
                            ImGui::EndTabItem();
                        }
                        ImGui::EndTabBar();
                    }else{

                    ImGui::BeginTabBar("##Tab 1");
                    if (ImGui::BeginTabItem("Multibot"))
                    {
                        active_tab = 1;
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Item DB"))
                    {
                        active_tab = 2;
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Executor"))
                    {
                        active_tab = 3;
                        ImGui::EndTabItem();
                    }
                    
                    if (ImGui::BeginTabItem("Account Info"))
                    {
                        active_tab = 300;
                        ImGui::EndTabItem();
                    }

                    // TAB 1 (MULTIBOT)
                    if (active_tab == 1)
                    {
                        ImGui::Spacing();
                        if (ImGui::BeginChild(XorStr("#1 BeginChild").c_str(), ImVec2(200, 347), true, 0))
                        {
                            if (ImGui::Checkbox("Select All", &selectall))
                            {
                                if (selectall)
                                {
                                    for (int i = 0; GrowtopiaBot bot : bots)
                                    {
                                        selected[i] = { true };
                                        bot.uname = bot.uname;
                                        i++;
                                    }
                                }
                                else {
                                    for (int i = 0; i < bots.size(); i++)
                                    {
                                        selected[i] = { false };
                                    }
                                }
                            }
                            const char* names[1000] = { "none" };
                            if (ImGui::BeginListBox("##Acclist", ImVec2(ImGui::GetWindowWidth() - 20, 227.f)))
                            {
                                for (int i = 0;GrowtopiaBot account : bots)
                                {
                                    if (ImGui::Selectable(account.uname.c_str(), &selected[i], 0))
                                    {
                                        for (int i = 0; i < bots.size(); i++)
                                        {
                                            names[i] = bots.at(i).uname.c_str();
                                            selectall = false;
                                            selected[i] = { false };
                                        }
                                        selected[i] = true;
                                    }
                                    i++;
                                }
                                ImGui::EndListBox();
                            }
                            ImGui::SetNextItemWidth(180.0f);
                            ImGui::InputTextWithHint(XorStr("##world1").c_str(), "Grow ID", usernamebot, sizeof(usernamebot), 0);
                            ImGui::SetNextItemWidth(180.0f);
                            ImGui::InputTextWithHint(XorStr("##world2").c_str(), "Password", passwordbot, sizeof(passwordbot), ImGuiInputTextFlags_Password);
                            if (ImGui::Button("Add", ImVec2(85, 20)))
                            {
                                if (bots.size() == 0) {
                                    create(usernamebot, passwordbot);
                                    loginpacket = true;
                                    current_item = 0;
                                }
                                else {
                                    create(usernamebot, passwordbot);
                                    loginpacket = true;

                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Remove", ImVec2(85, 20)))
                            {
                                if (!selectall)
                                {
                                    for (int i = 0; GrowtopiaBot const& account : bots)
                                    {
                                        if (selected[i])
                                        {
                                            bots.erase(bots.begin() + i);
                                            bot.WhenDisconnected();
                                        }
                                        i++;
                                    }
                                }
                            }

                            ImGui::EndChild();
                        }

                        ImGui::SameLine();
                        if (ImGui::BeginChild("#2 BeginChild", ImVec2(420, 347), true, 0))
                        {
                            ImGui::BeginTabBar("##Tab 2");
                            if (ImGui::BeginTabItem("Info")) {
                                active_tab = 4;
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Main")) {
                                active_tab = 5;
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Automation")) {
                                active_tab = 6;
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Spammer")) {
                                active_tab = 7;
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("World")) {
                                active_tab = 8;
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem("Inventory")) {
                                active_tab = 9;
                                ImGui::EndTabItem();
                            }
                            
                            if (ImGui::BeginTabItem("Debug")) {
                                active_tab = 10;
                                ImGui::EndTabItem();
                            }

                            // TAB 1.1 (INFO)
                            if (active_tab == 4)
                            {
                                if (bots.size() > 0) {
                                    if (selectall)
                                    {
                                        ImGui::Spacing();
                                        ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Select all bots is active.");
                                    }
                                    for (int i = 0; GrowtopiaBot bot : bots) {
                                        if (selected[i] && !selectall)
                                        {
                                            ImGui::Spacing();
                                            ImGui::Text("Selected: %s", bot.uname.c_str());
                                            ImGui::Text("Status: %s", bot.statusbot.c_str());
                                            ImGui::Text("Server: %s:%d", bot.serveripaddress, bot.serverportaddress);
                                            if (bot.inistatusbot)
                                            {
                                                ImGui::Text("Level: %d", bot.level);
                                                ImGui::Text("Gem amount: %d", bot.gem);
                                                ImGui::Text("Current world: %s", bot.currentworld.c_str());
                                                //ImGui::Text("World player count: %d", bot.worldplayercount);
                                                ImGui::Text("UserID: %d", bot.localuserid);
                                                ImGui::Text("NetID: %d", bot.localnetid);
                                                ImGui::Text("Position X: %d, Y: %d", (int)bot.localx / 32, (int)bot.localy / 32);
                                            }
                                        }
                                        i++;
                                    }
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.2 (MAIN)
                            if (active_tab == 5)
                            {
                                if (bots.size() > 0) {
                                    ImGui::Spacing();
                                    ImGui::PushItemWidth(140);
                                    ImGui::InputTextWithHint("##world3", "World", worldName, sizeof(worldName), 0);
                                    ImGui::SameLine();
                                    if (ImGui::Button("Warp", ImVec2(50, 0)))
                                    {
                                        for (int i = 0;auto & bot : bots)
                                        {
                                            if (selected[i]) {
                                                bot.worldName = worldName;
                                                bot.SendPacket(3, "action|join_request\nname|" + bot.worldName, bot.peer);
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::SameLine();
                                    ImGui::PushItemWidth(190);
                                    ImGui::SliderInt(XorStr("##Speed").c_str(), &speed, 1, 5, "%d Tile");
                                    if (ImGui::Checkbox("Auto Access", &autoacc)) {
                                        for (int i = 0;auto & bot : bots) {
                                            if (selected[i])
                                            {
                                                bot.autoAccess = true;
                                            }
                                            i++;
                                        }
                                    }
                                    else {
                                        bot.autoAccess = false;
                                    }
                                    ImGui::SetCursorPosX(286.0f);
                                    ImGui::SetCursorPosY(70.0f);
                                    if (ImGui::Button("Up", ImVec2(50, 50)))
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots) {
                                            if (selected[i])
                                            {
                                                bots.at(i).move(XorStr("up"), speed);
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::Spacing();
                                    ImGui::SetCursorPosX(228.0f);
                                    if (ImGui::Button("Left", ImVec2(50, 50)))
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots) {
                                            if (selected[i])
                                            {
                                                bots.at(i).move(XorStr("left"), speed);
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::SameLine();
                                    if (ImGui::Button("Use", ImVec2(50, 50)))
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots) {
                                            if (selected[i])
                                            {
                                                bot.use();
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::SameLine();
                                    if (ImGui::Button("Right", ImVec2(50, 50)))
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots) {
                                            if (selected[i])
                                            {
                                                bots.at(i).move(XorStr("right"), speed);
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::Spacing();
                                    ImGui::SetCursorPosX(286.0f);
                                    ImGui::SetCursorPosY(187.0f);
                                    if (ImGui::Button("Down", ImVec2(50, 50)))
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots) {
                                            if (selected[i])
                                            {
                                                bots.at(i).move(XorStr("down"), speed);
                                            }
                                            i++;
                                        }
                                    }
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.3 (Automation)
                            if (active_tab == 6)
                            {
                                if (bots.size() > 0) {
                                    ImGui::Spacing();
                                    for (int i = 0; GrowtopiaBot & bot : bots) {
                                        if (selected[i] && !selectall)
                                        {
                                            if (ImGui::Checkbox("Enable", &bot.enableautofarm))
                                            {
                                                std::thread enablePNB(&GrowtopiaBot::PNB, &bot, bot);
                                                enablePNB.detach();
                                            }
                                            ImGui::Checkbox("Auto Break", &bot.enableautobreak);
                                            ImGui::SameLine();
                                            ImGui::Checkbox("Auto Place", &bot.enableautoput);
                                            ImGui::InputInt("Items ID", &bot.itemData);
                                            if (ImGui::Checkbox("Auto Collect", &bots.at(current_item).autocollect))
                                            {
                                                std::thread collecting(autocollecting, bot.range);
                                                collecting.detach();
                                            };
					    ImGui::Checkbox("Collect Gems", &bots.at(current_item).collectgems);
                                        }
                                        i++;
                                    }
                                    if (ImGui::CollapsingHeader("Sellect Tile"))
                                    {
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[1])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[1] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[1] = false;
                                                }
                                                bool tile1 = ImGui::Button("##tile1", ImVec2(25, 25));
                                                if (tile1) { bot.buttoncolorchange[1] = 1 - bot.buttoncolorchange[1]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 2
                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[2])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[2] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[2] = false;
                                                }
                                                bool tile2 = ImGui::Button("##tile2", ImVec2(25, 25));
                                                if (tile2) { bot.buttoncolorchange[2] = 1 - bot.buttoncolorchange[2]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 3
                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[3])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[3] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[3] = false;
                                                }
                                                bool tile3 = ImGui::Button("##tile3", ImVec2(25, 25));
                                                if (tile3) { bot.buttoncolorchange[3] = 1 - bot.buttoncolorchange[3]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 4
                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[4])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[4] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[4] = false;
                                                }
                                                bool tile4 = ImGui::Button("##tile4", ImVec2(25, 25));
                                                if (tile4) { bot.buttoncolorchange[4] = 1 - bot.buttoncolorchange[4]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 5
                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[5])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[5] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[5] = false;
                                                }
                                                bool tile5 = ImGui::Button("##tile5", ImVec2(25, 25));
                                                if (tile5) { bot.buttoncolorchange[5] = 1 - bot.buttoncolorchange[5]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        //Line 2 // 6
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[6])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[6] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[6] = false;
                                                }
                                                bool tile6 = ImGui::Button("##tile6", ImVec2(25, 25));
                                                if (tile6) { bot.buttoncolorchange[6] = 1 - bot.buttoncolorchange[6]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[7])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[7] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[7] = false;
                                                }
                                                bool tile7 = ImGui::Button("##tile7", ImVec2(25, 25));
                                                if (tile7) { bot.buttoncolorchange[7] = 1 - bot.buttoncolorchange[7]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[8])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[8] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[8] = false;
                                                }
                                                bool tile8 = ImGui::Button("##tile8", ImVec2(25, 25));
                                                if (tile8) { bot.buttoncolorchange[8] = 1 - bot.buttoncolorchange[8]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[9])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[9] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[9] = false;
                                                }
                                                bool tile9 = ImGui::Button("##tile9", ImVec2(25, 25));
                                                if (tile9) { bot.buttoncolorchange[9] = 1 - bot.buttoncolorchange[9]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[10])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[10] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[10] = false;
                                                }
                                                bool tile10 = ImGui::Button("##tile10", ImVec2(25, 25));
                                                if (tile10) { bot.buttoncolorchange[10] = 1 - bot.buttoncolorchange[10]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 3
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[11])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[11] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[11] = false;
                                                }
                                                bool tile11 = ImGui::Button("##tile11", ImVec2(25, 25));
                                                if (tile11) { bot.buttoncolorchange[11] = 1 - bot.buttoncolorchange[11]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[12])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[12] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[12] = false;
                                                }
                                                bool tile12 = ImGui::Button("##tile12", ImVec2(25, 25));
                                                if (tile12) { bot.buttoncolorchange[12] = 1 - bot.buttoncolorchange[12]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        ImGui::Dummy(ImVec2(25, 25));                       // Player Middle
                                        ImGui::SameLine();

                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[13])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[13] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[13] = false;
                                                }
                                                bool tile13 = ImGui::Button("##tile13", ImVec2(25, 25));
                                                if (tile13) { bot.buttoncolorchange[13] = 1 - bot.buttoncolorchange[13]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[14])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[14] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[14] = false;
                                                }
                                                bool tile14 = ImGui::Button("##tile14", ImVec2(25, 25));
                                                if (tile14) { bot.buttoncolorchange[14] = 1 - bot.buttoncolorchange[14]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 4
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[15])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[15] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[15] = false;
                                                }
                                                bool tile15 = ImGui::Button("##tile15", ImVec2(25, 25));
                                                if (tile15) { bot.buttoncolorchange[15] = 1 - bot.buttoncolorchange[15]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[16])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[16] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[16] = false;
                                                }
                                                bool tile16 = ImGui::Button("##tile16", ImVec2(25, 25));
                                                if (tile16) { bot.buttoncolorchange[16] = 1 - bot.buttoncolorchange[16]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[17])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[17] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[17] = false;
                                                }
                                                bool tile17 = ImGui::Button("##tile17", ImVec2(25, 25));
                                                if (tile17) { bot.buttoncolorchange[17] = 1 - bot.buttoncolorchange[17]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[18])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[18] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[18] = false;
                                                }
                                                bool tile18 = ImGui::Button("##tile18", ImVec2(25, 25));
                                                if (tile18) { bot.buttoncolorchange[18] = 1 - bot.buttoncolorchange[18]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[19])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[19] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[19] = false;
                                                }
                                                bool tile19 = ImGui::Button("##tile19", ImVec2(25, 25));
                                                if (tile19) { bot.buttoncolorchange[19] = 1 - bot.buttoncolorchange[19]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        // 5
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[20])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[20] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[20] = false;
                                                }
                                                bool tile20 = ImGui::Button("##tile20", ImVec2(25, 25));
                                                if (tile20) { bot.buttoncolorchange[20] = 1 - bot.buttoncolorchange[20]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[21])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[21] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[21] = false;
                                                }
                                                bool tile21 = ImGui::Button("##tile21", ImVec2(25, 25));
                                                if (tile21) { bot.buttoncolorchange[21] = 1 - bot.buttoncolorchange[21]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[22])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[22] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[22] = false;
                                                }
                                                bool tile22 = ImGui::Button("##tile22", ImVec2(25, 25));
                                                if (tile22) { bot.buttoncolorchange[22] = 1 - bot.buttoncolorchange[22]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[23])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[23] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[23] = false;
                                                }
                                                bool tile23 = ImGui::Button("##tile23", ImVec2(25, 25));
                                                if (tile23) { bot.buttoncolorchange[23] = 1 - bot.buttoncolorchange[23]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }

                                        ImGui::SameLine();
                                        for (int i = 0; GrowtopiaBot & bot : bots)
                                        {
                                            if (selected[i] && !selectall)
                                            {
                                                if (bot.buttoncolorchange[24])
                                                {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.13f, 0.75f, 1.00f, 0.80f));
                                                    bot.buttoncolorchange[24] = true;
                                                }
                                                else {
                                                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.73f, 0.75f, 0.74f, 1.00f));
                                                    bot.buttoncolorchange[24] = false;
                                                }
                                                bool tile24 = ImGui::Button("##tile24", ImVec2(25, 25));
                                                if (tile24) { bot.buttoncolorchange[24] = 1 - bot.buttoncolorchange[24]; }
                                                ImGui::PopStyleColor(1);
                                            }
                                            i++;
                                        }
                                    }
                                    ImGui::Spacing();
                                    ImGui::SliderInt("##autocollect", &bots.at(current_item).range, 0, 10, "%d Range");
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.4 (Spammers)
                            if (active_tab == 7)
                            {
                                if (bots.size() > 0) {
                                    ImGui::Spacing();
                                    for (int i = 0; GrowtopiaBot & bot : bots) {
                                        if (selected[i] && !selectall)
                                        {
                                            // Auto Spam
                                            ImGui::SetNextItemWidth(400.0f);
                                            if (ImGui::Checkbox("Enable Auto Spam", &bot.autospamm)) {
                                                std::thread spam(spamthread, bot.spamtext1);
                                                spam.detach();
                                            }
                                            ImGui::SetNextItemWidth(400.0f);
                                            ImGui::InputTextWithHint("##textspam2", "Text Spam", bot.spamtext1, IM_ARRAYSIZE(bot.spamtext1));
                                            ImGui::SetNextItemWidth(335.0f);
                                            ImGui::InputInt("Delay##spam2", &bot.intervalspam, 1.0f, 6.0f);
                                            ImGui::SameLine();
                                            HelpMarker("Interval (in seconds)");

                                            // Auto Msg
                                            ImGui::Spacing();
                                            ImGui::SetNextItemWidth(400.0f);
                                            ImGui::Checkbox("Enable Auto /msg", &bot.automsgg);
                                            ImGui::SetNextItemWidth(400.0f);
                                            ImGui::InputTextWithHint("##textmsg3", "Text /msg When People Join", bot.msgtextt, IM_ARRAYSIZE(bot.msgtextt));
                                            ImGui::SetNextItemWidth(400.0f);
                                            ImGui::InputTextWithHint("##textmsg4", "Text /msg When People Left", bot.msgtexttt, IM_ARRAYSIZE(bot.msgtexttt));
                                        }
                                        i++;
                                    }
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.5 (World)
                            if (active_tab == 8)
                            {
                                if (bots.size() > 0) {
                                    if (ImGui::BeginTabBar(XorStr("##tabbar222").c_str())) {
                                        if (ImGui::BeginTabItem(XorStr("Players").c_str()))
                                        {
                                            if (loginpacket)
                                            {
                                                if (bots.at(current_item).currentWorld != XorStr("EXIT").c_str()) {
                                                    for (int i = 0; i < bots.at(current_item).objects.size(); i++) {
                                                        if (!bots.at(current_item).objects.at(i).isGone) { //complex
                                                            utils::replace(bots.at(current_item).objects.at(i).name, "``", "");
                                                            utils::replace(bots.at(current_item).objects.at(i).name, "`2", "");
                                                            utils::replace(bots.at(current_item).objects.at(i).name, "`w", "");
                                                            utils::replace(bots.at(current_item).objects.at(i).name, "`#@", "");
                                                            utils::replace(bots.at(current_item).objects.at(i).name, "`^", "");
                                                            if (ImGui::CollapsingHeader(bots.at(current_item).objects.at(i).name.c_str())) {
                                                                ImGui::Text("NetID: %d", bots.at(current_item).objects.at(i).netId);
                                                                ImGui::Text("Country: %s", bots.at(current_item).objects.at(i).country.c_str());
                                                                ImGui::Text("UserID: %d", bots.at(current_item).objects.at(i).userId);
                                                                ImGui::Text("Position X: %d, Y: %d", (int)bots.at(current_item).objects.at(i).x / 32, (int)bots.at(current_item).objects.at(i).y / 32);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            ImGui::EndTabItem();
                                        }
					 

					    
					if (ImGui::BeginTabItem(XorStr("GrowScan").c_str()))
                                        {
						/*
                                            if (loginpacket)
                                            {
                                                if (bots.at(current_item).currentWorld != XorStr("EXIT").c_str()) {
                                                    	static std::map<int, int> lastMap;
							if (ImGui::Button("Re Scan")) {
							lastMap = bot->GetAllObject();
							}

							for (auto& object : lastMap) {
							ImGui::Text("Item id: %d, amount: %d", object.first, object.second);
							}
                                                }*/
                                            }
                                            ImGui::EndTabItem();
                                        }
                                    }
                                    ImGui::EndTabBar();
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.6 (Inventory)
                            
                            if (active_tab == 9)
                            {
                                if (bots.size() > 0) {
                                    if (ImGui::BeginTabBar(XorStr("#tabbasdsdsdr222").c_str())) {
                                        if (ImGui::BeginTabItem(XorStr("##Item").c_str()))
                                        {
                                            if (loginpacket)
                                            {
                                                for (int i = 0; i < bots.at(current_item).inventory.size(); i++) {
                                                                ImGui::Text("ItemID X: %d, Amount: %d", (int)bots.at(current_item).inventory.at(i).id.c_str(), (int)bots.at(current_item).inventory.at(i).amount.c_str());
                                                    }
                                            }
                                            ImGui::EndTabItem();
                                   
                                        }
                                    }
                                    ImGui::EndTabBar();
                                }
                                else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }

                            // TAB 1.7 (Debug)
                            if (active_tab == 10)
                            {
                                if (bots.size() > 0) {
                                    editor2.Render("", ImVec2(400, 265), true); //height - 30
                                        for (int i = 0; i < bots.at(current_item).debug.size(); i++)
                                        {
                                            editor2.SetReadOnly(true);
                                            editor2.SetText(bots.at(current_item).debug.at(i).text.c_str());
                                            if (bots.at(current_item).debug.size() > 50)
                                            {
                                                bots.at(current_item).debug.erase(bots.at(current_item).debug.begin() + 0);
                                            }
                                            
                                        }
                                } else {
                                    ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.00f), "Add Bot First.");
                                }
                            }


                            ImGui::EndChild();
                        }
                    }

                    // TAB 2 Item DB
                    if (active_tab == 2)
                    {
                        if (ImGui::BeginChild(XorStr("#ItemDatas").c_str(), ImVec2(700, 347), true, 0))
                        {
                            static ImGuiTextFilter filter;
                            ImGui::Text("Search:");
                            filter.Draw("", 450);
                            ImGui::SameLine();
                            if (ImGui::Button("Load Items.dat", ImVec2(125, 25))) {
                                ItemList.clear();
                                Vectorting();
                            };
                            if (ImGui::BeginListBox("##ItemList", ImVec2(625, 280)))
                            {
                                for (int i = 0; i < ItemList.size(); i++) {
                                    auto paintkit = ItemList.at(i);
                                    if (filter.PassFilter(paintkit.c_str())) {
                                        std::string label = paintkit + "##" + std::to_string(i); //do this or you will have problems selecting elements with the same name

                                        if (ImGui::Selectable(label.c_str())) {

                                        }
                                    }

                                }
                                //ItemList.clear();
                                //ItemList.push_back("Dirt    2");
                                ImGui::EndListBox();
                            }
                            ImGui::EndChild();
                        }
                    }
                    if (active_tab == 3)
                    {
                        ImGui::Spacing();
                        if (ImGui::BeginChild(XorStr("#Acc").c_str(), ImVec2(200, 347), true, 0))
                        {
                                if (ImGui::Checkbox("Select All", &selectall))
                                {
                                    if (selectall)
                                    {
                                        for (int i = 0; GrowtopiaBot bot : bots)
                                        {
                                            selected[i] = { true };
                                            bot.uname = bot.uname;
                                            i++;
                                        }
                                    }
                                    else {
                                        for (int i = 0; i < bots.size(); i++)
                                        {
                                            selected[i] = { false };
                                        }
                                    }
                                }
                                const char* names[1000] = { "none" };
                                if (ImGui::BeginListBox("##Acclist", ImVec2(ImGui::GetWindowWidth() - 20, 227.f)))
                                {
                                    for (int i = 0;GrowtopiaBot account : bots)
                                    {
                                        if (ImGui::Selectable(account.uname.c_str(), &selected[i], 0))
                                        {
                                            for (int i = 0; i < bots.size(); i++)
                                            {
                                                names[i] = bots.at(i).uname.c_str();
                                                selectall = false;
                                                selected[i] = { false };
                                            }
                                            selected[i] = true;
                                        }
                                        i++;
                                    }
                                    ImGui::EndListBox();
                                }
                                ImGui::SetNextItemWidth(180.0f);
                                ImGui::InputTextWithHint(XorStr("##world1").c_str(), "Grow ID", usernamebot, sizeof(usernamebot), 0);
                                ImGui::SetNextItemWidth(180.0f);
                                ImGui::InputTextWithHint(XorStr("##world2").c_str(), "Password", passwordbot, sizeof(passwordbot), ImGuiInputTextFlags_Password);
                                if (ImGui::Button("Add", ImVec2(85, 20)))
                                {
                                    if (bots.size() == 0) {
                                        create(usernamebot, passwordbot);
                                        loginpacket = true;
                                        current_item = 0;
                                    }
                                    else {
                                        create(usernamebot, passwordbot);
                                        loginpacket = true;

                                    }
                                }
                                ImGui::SameLine();
                                if (ImGui::Button("Remove", ImVec2(85, 20)))
                                {
                                    if (!selectall)
                                    {
                                        for (int i = 0; GrowtopiaBot const& account : bots)
                                        {
                                            if (selected[i])
                                            {
                                                bots.erase(bots.begin() + i);
                                                bot.WhenDisconnected();
                                            }
                                            i++;
                                        }
                                    }
                                }

                            ImGui::EndChild();
                        }
                        ImGui::SameLine();
                        if (ImGui::BeginChild("#2 BegizxczxcnChild", ImVec2(420, 347), true, 0))
                        {
                        ImGui::Text("%d lines | %s", editor.GetTotalLines(), editor.GetCurrentLineText().c_str());
                        ImGui::InputTextWithHint("##Script", "Script.lua", namaFile, 40, 0);
                        ImGui::SameLine();


                        if (ImGui::Button("Save", ImVec2(40, 20))) {}


                        ImGui::SameLine();


                        if (ImGui::Button("Load", ImVec2(40, 20))) {}


                        editor.Render("", ImVec2(400, 265), true); //height - 30


                        if (ImGui::Button("Execute", ImVec2(85, 20))) {
                            executelua(editor.GetText());
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Stop", ImVec2(85, 20))) {
                            executelua("os.exit()");
                        }

                    }

                    ImGui::EndChild();
                    }
                    if (active_tab == 300)
                    {
                        ImGui::Spacing();
                        if (ImGui::BeginChild("#2 BegizxcdsdszxcnChild", ImVec2(420, 347), true, 0))
                        {
                            ImGui::Text("Username: %s", KeyAuthApp.data.username.c_str());
                            ImGui::Text("IP address: %s", KeyAuthApp.data.ip.c_str());
                            ImGui::Text("Hardware-Id: %s", KeyAuthApp.data.hwid.c_str());
                            ImGui::Text("Subscription expiry: %s", tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry))).c_str());
                            ImGui::Text("Create date: %s", tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.createdate))).c_str());


                        }

                        ImGui::EndChild();
                    }
                    }
                 }
                ImGui::End();
                ImGui::PopFont();
                ImGui::EndFrame();
            }
            else
            {
                exit(0);
            }
        }
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper Functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
