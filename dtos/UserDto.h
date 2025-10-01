#pragma once

#include <models/User.h>

using namespace drogon_model::postgres;

struct UserTokenDtoResponse
{
    std::int64_t id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::string token;

    explicit UserTokenDtoResponse(const User& user);

    [[nodiscard]] Json::Value toJson() const;
};

struct UserDetailsDtoResponse
{
    std::int64_t id;
    std::string firstName;
    std::string lastName;
    std::string email;
    bool isDeleted;
    std::string createdAt;
    std::string updatedAt;

    explicit UserDetailsDtoResponse(const User& user);

    [[nodiscard]] Json::Value toJson() const;
};