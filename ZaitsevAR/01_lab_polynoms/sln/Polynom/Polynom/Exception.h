#pragma once
#include <exception>
#include <iostream>
#include <string>

using namespace std;

class Exception : public exception
{
private:
	const string message;
public:
	Exception(string ex) : message(ex) {};
	char const* what() const
	{
		return message.c_str();
	}
};