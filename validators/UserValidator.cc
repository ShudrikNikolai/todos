#include "UserValidator.h"
// TODO
#include <cctype>
#include <regex>
#include <string>

bool isValidEmail(const std::string& email)
{
    // Use a regular expression to validate the email format.
    // This regex is a simple example and may not cover all valid email formats.
    const std::regex emailPattern(R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4})");
    return std::regex_match(email, emailPattern);
}

bool isStrongPassword(const std::string& password)
{
    // Define your password strength criteria here.
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (const char c : password)
    {
        if (std::isupper(c))
        {
            hasUppercase = true;
        }
        else if (std::islower(c))
        {
            hasLowercase = true;
        }
        else if (std::isdigit(c))
        {
            hasDigit = true;
        }
        else
        {
            // Define your special characters criteria here.
            if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%')
            {
                hasSpecialChar = true;
            }
        }
    }

    // Define your password strength requirements here.
    return password.length() >= 6 && hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

bool UserValidator::validateRegisterForm(const Json::Value& req, std::string& errorField,
                                         drogon_model::postgres::User& user)
{
    //? Check if fields exist in the JSON.
    if (!req.isMember("first_name"))
    {
        errorField = "first_name is missing";
        return false;
    }
    if (!req.isMember("last_name"))
    {
        errorField = "last_name is missing";
        return false;
    }
    if (!req.isMember("password"))
    {
        errorField = "password is missing";
        return false;
    }
    if (!req.isMember("email"))
    {
        errorField = "email is missing";
        return false;
    }

    //? Check the data types of the fields.
    if (!req["first_name"].isString())
    {
        errorField = "first_name is not a string";
        return false;
    }
    if (!req["last_name"].isString())
    {
        errorField = "last_name is not a string";
        return false;
    }
    if (!req["password"].isString())
    {
        errorField = "password is not a string";
        return false;
    }
    if (!req["email"].isString())
    {
        errorField = "email is not a string";
        return false;
    }

    const std::string firstName = req["first_name"].asString();
    const std::string lastName = req["last_name"].asString();
    const std::string password = req["password"].asString();
    const std::string email = req["email"].asString();

    if (!isStrongPassword(password))
    {
        errorField = "password is not strong enough";
        return false;
    }

    if (!isValidEmail(email))
    {
        errorField = "email is not valid";
        return false;
    }

    user.setFirstName(firstName);
    user.setLastName(lastName);
    user.setPassword(password);
    user.setEmail(email);

    return true;  // Validation passed.
}

bool UserValidator::validateLoginForm(const Json::Value& req, std::string& errorField,
                                      drogon_model::postgres::User& user)
{
    //? Check if fields exist in the JSON.
    if (!req.isMember("password"))
    {
        errorField = "password is missing";
        return false;
    }
    if (!req.isMember("email"))
    {
        errorField = "email is missing";
        return false;
    }

    //? Check the data types of the fields.
    if (!req["password"].isString())
    {
        errorField = "password is not a string";
        return false;
    }
    if (!req["email"].isString())
    {
        errorField = "email is not a string";
        return false;
    }

    const std::string password = req["password"].asString();
    const std::string email = req["email"].asString();

    if (!isValidEmail(email))
    {
        errorField = "email is not valid";
        return false;
    }

    user.setPassword(password);
    user.setEmail(email);

    return true;  // Validation passed.
}