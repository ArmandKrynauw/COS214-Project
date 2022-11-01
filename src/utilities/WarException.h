#ifndef WAREXCEPTION_H
#define WAREXCEPTION_H

#include <string>

class WarException : public std::exception {
public:
    WarException(std::string message, std::string errorCode = "");

    virtual const char *what() const

    noexcept;

    virtual const std::string error() const;

    virtual ~WarException();

protected:
    std::string message;
    std::string errorCode;
};

#endif // WAREXCEPTION_H