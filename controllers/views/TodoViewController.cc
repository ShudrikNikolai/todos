#include "TodoViewController.h"

void TodoViewController::todo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    HttpViewData data;
    data["name"] = req->getParameter("name");
    auto resp = HttpResponse::newHttpViewResponse("todos", data);
    callback(resp);
}