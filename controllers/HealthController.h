#pragma once

#include "BaseController.h"

#include <drogon/HttpController.h>

class HealthController final : public drogon::HttpController<HealthController>, public BaseController
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::health, "/health", HttpMethod::Get);
    METHOD_LIST_END

    void health(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
