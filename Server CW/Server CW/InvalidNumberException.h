#pragma once
#include "CW.h"
#include <exception>
class InvalidNumberException :public exception
{
public:
	string errorMessage;
	InvalidNumberException(string error) :errorMessage(error) {}
	const char* what() const noexcept { return errorMessage.c_str(); }
	~InvalidNumberException() {};
};