//
// Created by Mark Muranov on 1/23/24.
//

#pragma once

#include "Debug.h"
#include <variant>
#include <iostream>
#include <string>
#include <sstream>

namespace ECE141
{

// Result type used to store values and errors.
// Can NOT hold an error and value at the same time.
// Error type NEEDS to be string stream streamable.
template<typename T, typename E = std::string>
class Result
{
protected:
    struct Ok { T value; };
    struct Error { E value; };

    Result() = default;

public:
    // Factory constructors for valid valued Result
    static Result newOk(const T& aValue)
    {
        Result newResult;
        newResult.value = Ok{ aValue };
        return newResult;
    }

    // Factory constructors for error Result
    static Result newError(const E& anError)
    {
        Result newResult;
        newResult.value = Error{ anError };
        return newResult;
    }

    // Returns `true` if Result holds a valid value (NOT an error).
    bool isOk() const {
        return std::holds_alternative<Ok>(value);
    }

    // Returns `true` if Result holds an error (NOT a valid value).
    bool isError() const {
        return std::holds_alternative<Error>(value);
    }

    // Retrieve value, will throw an error if a Result holds an error.
    T unwrap() const {
        if (isOk())
            return std::get<Ok>(value).value;

        std::stringstream errorMessage;
        errorMessage << "Attempted to unwrap Error value: " << std::get<Error>(value).value;
        throw std::logic_error(errorMessage.str());
    }

    T unwrapOr(const T& defaultValue) const
    {
        if (isError())
            return defaultValue;

        return std::get<Ok>(value).value;
    }

    E unwrapError() const
    {
        if (isError())
            return std::get<Error>(value).value;

        std::stringstream errorMessage;
        errorMessage << "Attempted to unwrap Ok value: " << std::get<Ok>(value).value;
        throw std::logic_error(errorMessage.str());
    }

    // Get the valid value without throwing an error.
    // CAREFUL: It is your responsibility to check that Result has a valid value.
    T getOk() const
    {
        ASSERT(isOk()); // This method can only be called when there is a valid value
        return std::get<Ok>(value).value;
    }

    // Get the error without throwing an error.
    // CAREFUL: It is your responsibility to check that Result has an error.
    E getError() const
    {
        ASSERT(isError()); // This method can only be called when there is an error
        return std::get<Error>(value).value;
    }

protected:
    std::variant<Ok, Error> value;

};

} // namespace ECE141

