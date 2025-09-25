#include <drogon/drogon.h>
int main()
{
    // LOG_DEBUG << "Load config file";
    drogon::app().loadConfigFile("../config.json");

    // LOG_DEBUG << "Running on http://localhost:4000";
    drogon::app()
        .setThreadNum(16)
        .enableRunAsDaemon()
        .run();
    return EXIT_SUCCESS;
    // drogon::app()
    //     .setLogPath("./")
    //     .setLogLevel(trantor::Logger::kWarn)
    //     .addListener("0.0.0.0", 4000)
    //     .setThreadNum(16)
    //     .enableRunAsDaemon()
    //     .run();
}