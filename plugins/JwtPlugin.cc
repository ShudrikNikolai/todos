/**
 *
 *  JwtPlugin.cc
 *
 */

#include "JwtPlugin.h"

#include <drogon/drogon.h>

using namespace drogon;

void JwtPlugin::initAndStart(const Json::Value& config)
{
    LOG_DEBUG << "JWT initialized and Start";
    this->config = config;
}

void JwtPlugin::shutdown()
{
    LOG_DEBUG << "JWT shut down";
}

auto JwtPlugin::init() const -> Jwt
{
    const auto secret = config.get("jwt-secret", "secret").asString();
    const auto sessionTime = config.get("jwt-sessionTime", 3600).asInt();
    const auto issuer = config.get("jwt-issuer", "auth0").asString();
    Jwt jwt(secret, sessionTime, issuer);
    return jwt;
}