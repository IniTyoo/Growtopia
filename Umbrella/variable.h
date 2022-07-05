#include "include.h"

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
bool asdhgsahdasvdsagsbdadhasgdbsajhdsauhdsajhdjashdjahsd = true;

string word = "";
string name = "";
string last;
