#ifndef WAREXCEPTION_H
#define WAREXCEPTION_H

#include <string>
#include "json.hpp"

class WarException : public std::exception {
public:
    WarException(std::string message, std::string errorCode = "");
    virtual const char *what() const noexcept;
    virtual const std::string error() const;
    nlohmann::json getJSON() const;
    virtual ~WarException();

protected:
    std::string message;
    std::string errorCode;
};

#endif // WAREXCEPTION_H