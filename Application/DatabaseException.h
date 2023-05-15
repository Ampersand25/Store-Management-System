#pragma once

#include "Exception.h"

class DatabaseException : public Exception // clasa DatabaseException este o clasas derivata din clasa de baza Exception
{
public:
	// DatabaseException() = delete;

	DatabaseException(const string& msg) : Exception(msg) {

	}

	/*
	DatabaseException(const string& msg) : Exception{ msg } {

	}
	*/
};