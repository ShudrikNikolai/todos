#pragma once

#include "models/Todo.h"

#include <drogon/HttpSimpleController.h>

using namespace drogon_model::postgres;

class TodoValidator
{
  public:
    static bool validateCreateForm(const Json::Value& req, std::string& errorField, Todo& todo);

    static bool validateUpdateForm(const Json::Value& req, std::string& errorField, Todo& todo);
};