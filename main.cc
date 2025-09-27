#include <drogon/drogon.h>

int main()
{
    drogon::app().loadConfigFile("../config.yaml");

    LOG_DEBUG << "Running on http://localhost:4000/health";
    drogon::app().run();

    return EXIT_SUCCESS;
}