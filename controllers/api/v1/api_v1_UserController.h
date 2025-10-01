#pragma once

#include "BaseController.h"
#include "models/User.h"

#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

namespace api
{
    namespace v1
    {
        class users final : public drogon::HttpController<users>, public BaseController
        {
          public:
            METHOD_LIST_BEGIN
            // api/v1/users/
            METHOD_ADD(users::get, "/", HttpMethod::Get, "LoginFilter");
            // api/v1/users/userId
            METHOD_ADD(users::getOne, "/{1}", HttpMethod::Get, "LoginFilter");
            // api/v1/users/userId
            METHOD_ADD(users::updateOne, "/{1}", HttpMethod::Put, "LoginFilter");
            // api/v1/users/userId

            METHOD_ADD(users::deleteOne, "/{1}", HttpMethod::Delete, "LoginFilter");

            // api/v1/users/me
            METHOD_ADD(users::getMe, "/me", HttpMethod::Get, "LoginFilter");
            // api/v1/users/me
            METHOD_ADD(users::updateMe, "/me", HttpMethod::Put, "LoginFilter");
            // api/v1/users/me
            METHOD_ADD(users::deleteMe, "/me", HttpMethod::Delete, "LoginFilter");
            METHOD_LIST_END

            void get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void getOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId);

            void updateOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback,
                           int userId);

            void deleteOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback,
                           int userId);

            void getMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void updateMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void deleteMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

          private:
            DbClientPtr client;

            void connect();
        };
    }  // namespace v1
}  // namespace api
