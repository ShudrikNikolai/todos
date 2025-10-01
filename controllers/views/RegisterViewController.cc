#include "RegisterViewController.h"

void RegisterViewController::reg(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    HttpViewData data;
    data["name"] = req->getParameter("name");
    auto resp = HttpResponse::newHttpViewResponse("reg", data);
    callback(resp);
}
