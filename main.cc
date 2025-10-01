#include <drogon/drogon.h>

int main()
{
    drogon::app().loadConfigFile("../config.yaml");
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