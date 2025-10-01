#pragma once

#include "controllers/BaseController.h"
#include "dtos/UserDto.h"
#include "models/User.h"

#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

namespace api
{
    namespace v1
    {
        class auth final : public HttpController<auth>, public BaseController
        {
          public:
            METHOD_LIST_BEGIN
            // api/v1/auth/register
            METHOD_ADD(auth::registerUser, "/register", HttpMethod::Post);
            // api/v1/auth/login
            METHOD_ADD(auth::loginUser, "/login", HttpMethod::Post);
            METHOD_LIST_END

            void registerUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void loginUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

          private:
            DbClientPtr client;

            void connect();

            static bool isUserAvailable(const User& user, Mapper<User>& mp);
        };
    }  // namespace v1
}  // namespace api
