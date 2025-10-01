/**
 *
 *  JwtPlugin.h
 *
 */

#pragma once

#include "Jwt.h"

#include <drogon/plugins/Plugin.h>

class JwtPlugin final : public drogon::Plugin<JwtPlugin>
{
  public:
    void initAndStart(const Json::Value& config) override;

    void shutdown() override;

    [[nodiscard]] auto init() const -> Jwt;

  private:
    Json::Value config;
};