#include "api_v2_TodosController.h"

#include "dtos/UserDto.h"

using namespace api::v2;

// Add definition of your processing function here

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

void todos::connect()
{
    LOG_DEBUG << "todos connect #1: ";

    client = app().getDbClient();
}

void todos::get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "Received request #1: ";

    connect();

    LOG_DEBUG << "Received request #2: ";

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
