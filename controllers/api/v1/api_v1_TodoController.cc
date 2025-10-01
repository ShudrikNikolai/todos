#include "api_v1_TodoController.h"

#include "dtos/UserDto.h"

using namespace api::v1;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

void todos::connect()
{
    client = app().getDbClient();
}

void todos::create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        std::shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        drogon_model::postgres::Todo todo = drogon_model::postgres::Todo();

        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            todo.setUserId(userId);
            auto dbTodo = mp.insertFuture(todo).get();
            Json::Value ret = dbTodo.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            LOG_DEBUG << e.base().what();
            Json::Value error;
            error["error"] = "Database error";
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

void todos::get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM todo");

            if (result.empty())
            {
                Json::Value ret;
                ret["results"] = Json::Value(Json::arrayValue);
                std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
                callback(response);
            }

            int totalRecords = result[0]["count"].as<int>();

            auto dbTodos = mp.findAll();

            Json::Value todosJson;
            for (auto& dbTodo : dbTodos)
            {
                Json::Value todoJson;
                todoJson = dbTodo.toJson();
                todosJson.append(todoJson);
            }

            Json::Value ret;

            ret["results"] = !todosJson.isNull() ? todosJson : Json::Value(Json::arrayValue);

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

void todos::getOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int todoId)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            auto dbTodo = mp.findByPrimaryKey(todoId);
            Json::Value ret = dbTodo.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
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

void todos::update(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int todoId)
{
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    std::shared_ptr<Json::Value> jsonBody = req->getJsonObject();
    auto reqTodo = drogon_model::postgres::Todo();

    connect();

    if (client)
    {
        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            auto updateTodo = mp.findByPrimaryKey(todoId);

            if (reqTodo.getTitle() != nullptr) updateTodo.setTitle(*reqTodo.getTitle());
            if (reqTodo.getDescription() != nullptr) updateTodo.setDescription(*reqTodo.getDescription());

            mp.update(updateTodo);
            Json::Value ret = updateTodo.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;
            if (s)
            {
                error["error"] = "Todo record not found";
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

void todos::deleteOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int todoId)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();

        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            mp.deleteByPrimaryKey(todoId);

            Json::Value ret;
            ret["message"] = "Todo deleted successfully";
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            const auto* s = dynamic_cast<const UnexpectedRows*>(&e.base());
            Json::Value error;

            if (s)
            {
                error["error"] = "Todo record not found";
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

void todos::createMyTodo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    connect();

    if (client)
    {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        std::shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        drogon_model::postgres::Todo todo = drogon_model::postgres::Todo();

        Mapper<drogon_model::postgres::Todo> mpTodo(client);

        try
        {
            todo.setUserId(userId);
            auto dbTodo = mpTodo.insertFuture(todo).get();

            Json::Value ret = dbTodo.toJson();
            std::shared_ptr<HttpResponse> response = handleResponse(ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException& e)
        {
            LOG_DEBUG << e.base().what();

            Json::Value error;
            error["error"] = "Database error";
            error["message"] = e.base().what();
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

void todos::getMyTodos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::string method = req->methodString();

    connect();

    if (client)
    {
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        Mapper<drogon_model::postgres::Todo> mp(client);

        try
        {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM todo WHERE user_id=$1", userId);

            if (result.empty())
            {
                Json::Value ret;
                ret["results"] = Json::Value(Json::arrayValue);
                std::shared_ptr<HttpResponse> response = handleResponse(ret, k200OK);
                callback(response);
            }

            int totalRecords = result[0]["count"].as<int>();

            auto dbTodos = mp.findBy(Criteria(Todo::Cols::_user_id, CompareOperator::EQ, userId));

            Json::Value todosJson;
            for (auto& dbTodo : dbTodos)
            {
                Json::Value todoJson;
                todoJson = dbTodo.toJson();
            }

            Json::Value ret;

            ret["results"] = !todosJson.isNull() ? todosJson : Json::Value(Json::arrayValue);

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
    }
}