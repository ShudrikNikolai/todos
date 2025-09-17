#include <drogon/drogon.h>
using namespace drogon;
int main()
{
    // app().loadConfigFile("./config.json").run();
        app().setLogPath("./")
         .setLogLevel(trantor::Logger::kWarn)
         .addListener("0.0.0.0", 4000)
         .setThreadNum(16)
         .enableRunAsDaemon()
         .run();
}