#pragma once

#include "BaseController.h"

#include <drogon/HttpController.h>

class RegisterViewController final : public drogon::HttpController<RegisterViewController>, public BaseController
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RegisterViewController::reg, "/register", drogon::HttpMethod::Get);
    METHOD_LIST_END

    void reg(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
