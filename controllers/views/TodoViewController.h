#pragma once

#include "filters/LoginFilter.h"
#include "BaseController.h"

#include <drogon/HttpController.h>

using namespace drogon;
class TodoViewController : public drogon::HttpController<TodoViewController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(TodoViewController::todo, "/todo", HttpMethod::Get, "LoginFilter");
    METHOD_LIST_END

    void todo(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
