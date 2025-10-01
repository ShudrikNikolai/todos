#include "UserDto.h"

#include "plugins/JwtPlugin.h"

#include <drogon/drogon.h>

UserTokenDtoResponse::UserTokenDtoResponse(const User& user)
{
    auto* jwtPtr = drogon::app().getPlugin<JwtPlugin>();
    auto jwt = jwtPtr->init();
    token = jwt.encode("user_id", static_cast<int>(user.getValueOfId()));
    id = user.getValueOfId();
    firstName = user.getValueOfFirstName();
    lastName = user.getValueOfLastName();
    email = user.getValueOfEmail();
}

Json::Value UserTokenDtoResponse::toJson() const
{
    Json::Value ret{};
    ret["id"] = id;
    ret["first_name"] = firstName;
    ret["last_name"] = lastName;
    ret["email"] = email;
    ret["token"] = token;
    return ret;
}

UserDetailsDtoResponse::UserDetailsDtoResponse(const User& user)
{
    id = user.getValueOfId();
    firstName = user.getValueOfFirstName();
    lastName = user.getValueOfLastName();
    email = user.getValueOfEmail();
    isDeleted = user.getValueOfIsDeleted();
    createdAt = user.getCreatedAt() ? user.getCreatedAt()->toDbStringLocal() : "";
    updatedAt = user.getUpdatedAt() ? user.getUpdatedAt()->toDbStringLocal() : "";
}

Json::Value UserDetailsDtoResponse::toJson() const
{
    Json::Value ret{};
    ret["id"] = id;
    ret["first_name"] = firstName;
    ret["last_name"] = lastName;
    ret["email"] = email;
    ret["is_deleted"] = isDeleted;
    ret["created_at"] = !createdAt.empty() ? createdAt : Json::Value();
    ret["updated_at"] = !updatedAt.empty() ? updatedAt : Json::Value();
    return ret;
}