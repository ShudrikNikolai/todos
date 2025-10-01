#pragma once

#include "BaseController.h"
#include "models/Todo.h"

#include <drogon/HttpController.h>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

namespace api
{
    namespace v2
    {
        class todos final : public drogon::HttpController<todos>, public BaseController
        {
          public:
            METHOD_LIST_BEGIN
            // api/v2/todos/counts
            METHOD_ADD(todos::get, "/counts", HttpMethod::Get);
            METHOD_LIST_END

            void get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

          private:
            DbClientPtr client;

            void connect();
        };
    }  // namespace v2
}  // namespace api
