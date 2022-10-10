#include "WarException.h"

WarException::WarException(std::string message, std::string errorCode) {
	this->message = message;	
	this->errorCode = errorCode;
}

const char* WarException::what() const noexcept {
	return message.c_str();	
}

const std::string WarException::error() const {
	return errorCode;	
}

WarException::~WarException() { };
