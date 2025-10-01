#pragma once

#include "models/User.h"

#include <drogon/HttpSimpleController.h>

using namespace drogon_model::postgres;

class UserValidator
{
  public:
    static bool validateRegisterForm(const Json::Value& req, std::string& errorField, User& user);

    static bool validateLoginForm(const Json::Value& req, std::string& errorField, User& user);
};