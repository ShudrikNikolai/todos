#pragma once

#include "BaseController.h"

#include <drogon/HttpController.h>

using namespace drogon;

class LoginViewController final : public drogon::HttpController<LoginViewController>, public BaseController
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LoginViewController::login, "/login", HttpMethod::Get);
    METHOD_LIST_END

    void login(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
