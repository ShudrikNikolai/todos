#include <drogon/drogon.h>

int main() {
    LOG_DEBUG << "Load config file";
    drogon::app().loadConfigFile("../config.json");

    LOG_DEBUG << "Running on http://localhost:4000";
    drogon::app().run();
    return EXIT_SUCCESS;
}