#include <drogon/drogon.h>

int main()
{
    const char* configPath = std::getenv("CONFIG_PATH");
    if (!configPath) {
        configPath = "../config.yaml";
    }
    
    drogon::app().loadConfigFile(configPath);

    // drogon::app().createDbClient("postgresql", "drogon-db", 5432, "postgres", "lstfng", "lstfng", 1, "default");
    drogon::app().registerHandler(
        "/",
        [](const drogon::HttpRequestPtr& request, std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setBody("Drogon API Todo");
            callback(resp);
        },
        {drogon::HttpMethod::Get});

    LOG_DEBUG << "Running on http://localhost:4000/";

    drogon::app().run();

    return EXIT_SUCCESS;
}