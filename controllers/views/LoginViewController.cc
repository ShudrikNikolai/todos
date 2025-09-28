#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>

using namespace drogon;

void LoginViewController::login(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    public:
    PATH_LIST_BEGIN
    // Also unlike HttpContoller, HttpSimpleController does not automatically
    // prepend the namespace and class name to the path. Thus the path of this
    // controller is at "/view".
    PATH_ADD("/login");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        HttpViewData data;
        data["name"] = req->getParameter("name");
        auto resp = HttpResponse::newHttpViewResponse("login", data);
        callback(resp);
    }
}
