#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
namespace v1
{
class Users : public drogon::HttpController<Users>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(Users::login, "/token?userId={1}&passwd{2}", Post); // path is /api/v1/Users/{arg2}/{arg1}
    METHOD_ADD(Users::me, "/{1}/me?token={2}", Get); // path is /api/v1/Users/{arg1}/me/{arg2}
    // ADD_METHOD_TO(Users::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END

    void login(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userId,
               const std::string &passwd);

    void me(const HttpRequestPtr &req,
            std::function<void (const HttpResponsePtr &)> &&callback,
            std::string userId,
            const std::string &token) const;
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
}
}
