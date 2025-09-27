#include "HealthController.h"

void HealthController::health(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&&callback)
{
    Json::Value ret;
    ret["result"] = "ok";
    std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
    callback(response);
}