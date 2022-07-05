#include "include.h"

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

static void autocollecting(int range)
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
