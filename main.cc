#include <drogon/drogon.h>
using namespace drogon;
int main() {
    app()
        .loadConfigFile("./config.json")
        .run();

    return EXIT_SUCCESS;
}