#pragma once

#include "BaseController.h"
#include "models/Todo.h"

#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

namespace api
{
    namespace v1
    {
        class todos final : public HttpController<todos>, public BaseController
        {
          public:
            METHOD_LIST_BEGIN
            // api/v1/todos?userId={1}
            METHOD_ADD(todos::create, "/?userId={1}", HttpMethod::Post, "LoginFilter");
            // api/v1/todos/
            METHOD_ADD(todos::get, "/", HttpMethod::Get, "LoginFilter");
            // api/v1/todos/todoId
            METHOD_ADD(todos::getOne, "/{1}", HttpMethod::Get, "LoginFilter");
            // api/v1/todos/todoId
            METHOD_ADD(todos::update, "/{1}", HttpMethod::Put, "LoginFilter");
            // api/v1/todos/todoId
            METHOD_ADD(todos::deleteOne, "/{1}", HttpMethod::Delete, "LoginFilter");
            // api/v1/todos/me
            METHOD_ADD(todos::createMyTodo, "/me", HttpMethod::Post, "LoginFilter");
            // api/v1/todos/me
            METHOD_ADD(todos::getMyTodos, "/me", HttpMethod::Get, "LoginFilter");
            METHOD_LIST_END

            void create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int userId);

            void createMyTodo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void getMyTodos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

            void getOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int postId);

            void update(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int postId);

            void deleteOne(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback,
                           int postId);

          private:
            DbClientPtr client;

            void connect();
        };
    }  // namespace v1
}  // namespace api
