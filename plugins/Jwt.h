/**
 *
 *  Jwt.h
 *
 */

#pragma once

#include <jwt-cpp/jwt.h>
#include <string>

class Jwt
{
  public:
    Jwt(std::string secret, int sessionTime, std::string issuer);

    [[nodiscard]] auto encode(const std::string& field, int value) const -> std::string;

    [[nodiscard]] auto decode(const std::string& token) const -> jwt::decoded_jwt<jwt::traits::kazuho_picojson>;

  private:
    std::string secret;
    int sessionTime;
    std::string issuer;
};