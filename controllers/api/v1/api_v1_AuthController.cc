#include "api_v1_AuthController.h"

#include "plugins/JwtPlugin.h"
#include "validators/UserValidator.h"

#include <external/libbcrypt/include/bcrypt/BCrypt.hpp>

using namespace api::v1;

using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

void auth::connect()
{
    client = app().getDbClient();
}

void auth::registerUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        User user = User();

        if (string errorField; !UserValidator::validateRegisterForm(*jsonBody, errorField, user))
        {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(error, k400BadRequest);
            callback(response);
            return;
        }

        Mapper<User> mp(client);

        if (!isUserAvailable(user, mp))
        {
            Json::Value error;
            error["error"] = "User already exists";
            shared_ptr<HttpResponse> response = handleResponse(error, k400BadRequest);
            callback(response);
            return;
        }

        try
        {
            LOG_DEBUG << "Inserting user" << user.getValueOfFirstName();
            user.setPassword(BCrypt::generateHash(user.getValueOfPassword()));
            user.setCreatedAt(trantor::Date::now());
            auto db_user = mp.insertFuture(user).get();
            auto userWithToken = UserTokenDtoResponse(db_user);
            Json::Value ret = userWithToken.toJson();
            shared_ptr<HttpResponse> response = handleResponse(ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            LOG_ERROR << e.base().what();
            Json::Value ret{};
            ret["error"] = "Database error";
            shared_ptr<HttpResponse> response = handleResponse(ret, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

void auth::loginUser(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();

        User user = User();

        if (string errorField; !UserValidator::validateLoginForm(*jsonBody, errorField, user))
        {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(error, k400BadRequest);
            callback(response);
            return;
        }

        Mapper<User> mp(client);

        auto criteria = Criteria(User::Cols::_email, CompareOperator::EQ, user.getValueOfEmail());
        auto users = mp.findBy(criteria);
        if (users.empty())
        {
            Json::Value error;
            error["error"] = "User does not exist";
            error["error_detail"] = "Password or Email is incorrect";
            shared_ptr<HttpResponse> response = handleResponse(error, k400BadRequest);
            callback(response);
            return;
        }

        auto userFromDb = users[0];
        if (!BCrypt::validatePassword(user.getValueOfPassword(), userFromDb.getValueOfPassword()))
        {
            Json::Value error;
            error["error"] = "Invalid password";
            error["error_detail"] = "Password or Email is incorrect";
            shared_ptr<HttpResponse> response = handleResponse(error, k400BadRequest);
            callback(response);
            return;
        }

        auto userWithToken = UserTokenDtoResponse(userFromDb);
        Json::Value ret = userWithToken.toJson();
        shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
        callback(response);
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

bool auth::isUserAvailable(const User& user, Mapper<User>& mp)
{
    const auto criteria = Criteria(User::Cols::_email, CompareOperator::EQ, user.getValueOfEmail());
    return mp.findFutureBy(criteria).get().empty();
}
