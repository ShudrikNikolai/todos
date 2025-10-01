#include "api_v1_UserController.h"

#include "dtos/UserDto.h"

#include <drogon/orm/DbClient.h>

using namespace api::v1;

// Add definition of your processing function here
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

template <>
inline User fromJson(const Json::Value& json)
{
    auto user = User(json);
    return user;
}

void users::connect()
{
    client = app().getDbClient();
}

//? GET /users/
void users::get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<User> mp(client);

        try
        {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM user_");

            if (result.empty())
            {
                Json::Value ret;
                ret["results"] = Json::Value(Json::arrayValue);
                std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
                callback(response);
            }

            auto totalRecords = result[0][0].as<int>();

            auto dbUsers = mp.findAll();

            Json::Value userJson;
            for (auto& user : dbUsers)
            {
                userJson.append(UserDetailsDtoResponse(user).toJson());
            }

            Json::Value ret;

            ret["results"] = !userJson.isNull() ? userJson : Json::Value(Json::arrayValue);

            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            Json::Value error;
            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? GET /users/{id}
void users::getOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<User> mp(client);

        try
        {
            auto user = mp.findByPrimaryKey(userId);

            Json::Value ret;
            ret = user.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "Record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? PUT /users/{id}
void users::updateOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        std::shared_ptr<Json::Value> jsonBody = req->getJsonObject();

        User user = fromJson<User>(*jsonBody);

        Mapper<User> mp(client);

        try
        {
            auto updateUser = mp.findByPrimaryKey(userId);

            if (user.getFirstName() != nullptr) updateUser.setFirstName(*user.getFirstName());
            if (user.getLastName() != nullptr) updateUser.setLastName(*user.getLastName());
            updateUser.setUpdatedAt(trantor::Date::now());

            mp.update(updateUser);

            Json::Value ret;
            ret = updateUser.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? DELETE /users/{id}
void users::deleteOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId)
{
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    connect();

    if (client)
    {
        Mapper<User> mp(client);

        try
        {
            auto user = mp.findByPrimaryKey(userId);

            user.setIsDeleted(true);

            mp.update(user);

            Json::Value ret;
            ret = user.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? GET /me
void users::getMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    int64_t userId = stoll(req->getHeader("user_id"));
    LOG_DEBUG << "Received userId: " << userId << " " << req->path();

    connect();

    if (client)
    {
        Mapper<User> mp(client);

        try
        {
            auto user = mp.findByPrimaryKey(userId);

            Json::Value ret;
            ret = user.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;
            LOG_DEBUG << "Received s: " << s << " " << req->path();

            if (s)
            {
                error["error"] = "Record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? PUT /me
void users::updateMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        std::shared_ptr<Json::Value> jsonBody = req->getJsonObject();

        int64_t userId = stoll(req->getHeader("user_id"));

        User user = fromJson<User>(*jsonBody);

        Mapper<User> mp(client);

        try
        {
            auto updateUser = mp.findByPrimaryKey(userId);

            if (user.getFirstName() != nullptr) updateUser.setFirstName(*user.getFirstName());
            if (user.getLastName() != nullptr) updateUser.setLastName(*user.getLastName());
            updateUser.setUpdatedAt(trantor::Date::now());

            mp.update(updateUser);

            Json::Value ret;
            ret = updateUser.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
    else
    {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
        callback(response);
    }
}

//? DELETE /me
void users::deleteMe(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    int userId = stoi(req->getHeader("user_id"));

    connect();

    if (client)
    {
        Mapper<User> mp(client);

        try
        {
            mp.deleteByPrimaryKey(userId);

            Json::Value ret;
            ret["message"] = "User deleted successfully";
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                std::shared_ptr<HttpResponse> response = handleResponse(error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
            std::shared_ptr<HttpResponse> response = handleResponse(error, k500InternalServerError);
            callback(response);
        }
    }
}