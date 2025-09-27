#include "BaseController.h"

void BaseController::getHeaders(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    const Json::Value response;
    const auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
    resp->addHeader("Access-Control-Allow-Methods", "OPTIONS,POST,GET");
    callback(resp);
}

void BaseController::getByIdHeaders(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback,
                                    const std::string& userId)
{
    const Json::Value response;
    const auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
    resp->addHeader("Access-Control-Allow-Methods", "OPTIONS,DELETE,PUT,GET");
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    callback(resp);
}