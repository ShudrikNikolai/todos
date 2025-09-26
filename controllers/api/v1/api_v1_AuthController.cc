#include "api_v1_AuthController.h"

using namespace api::v1;

void AuthController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}
