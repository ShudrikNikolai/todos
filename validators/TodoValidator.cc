#include "TodoValidator.h"

#include <regex>
#include <string>

bool TodoValidator::validateCreateForm(const Json::Value& req, std::string& errorField,
                                       drogon_model::postgres::Todo& todo)
{
    //? Check if fields exist in the JSON
    if (!req.isMember("description"))
    {
        errorField = "description is missing";
        return false;
    }

    //? Check the data types of the fields
    if (!req["description"].isString())
    {
        errorField = "description is not a string";
        return false;
    }

    const std::string description = req["description"].asString();

    todo.setDescription(description);

    return true;
}

bool TodoValidator::validateUpdateForm(const Json::Value& req, std::string& errorField,
                                       drogon_model::postgres::Todo& todo)
{
    if (req.isMember("description") && req["description"].isString())
    {
        const std::string description = req["description"].asString();

        todo.setDescription(description);
    }

    return true;
}