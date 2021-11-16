#pragma once

#include "Exception.h"

class CosException : public Exception // clasa CosException este o clasas derivata din clasa de baza Exception
{
public:
	// CosException() = delete;

	CosException(const string& msg) : Exception(msg) {

	}

	/*
	CosException(const string& msg) : Exception{ msg } {

	}
	*/
};