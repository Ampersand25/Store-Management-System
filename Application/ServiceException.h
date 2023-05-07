#pragma once

#include "Exception.h"

class ServiceException : public Exception // clasa ServiceException este o clasas derivata din clasa de baza Exception
{
public:
	// ServiceException() = delete;

	ServiceException(const string& msg) : Exception(msg) {

	}

	/*
	ServiceException(const string& msg) : Exception{ msg } {

	}
	*/
};