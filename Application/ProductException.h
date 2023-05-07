#pragma once

#include "Exception.h"

class ProductException : public Exception // clasa ProductException este o clasas derivata din clasa de baza Exception
{
public:
	// ProductException() = delete;

	ProductException(const string& msg) : Exception(msg) {

	}

	/*
	ProductException(const string& msg) : Exception{ msg } {

	}
	*/
};