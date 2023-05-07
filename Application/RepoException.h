#pragma once

#include "Exception.h"

class RepoException : public Exception // clasa RepoException este o clasas derivata din clasa de baza Exception
{
public:
	// RepoException() = delete;

	RepoException(const string& msg) : Exception(msg) {

	}

	/*
	RepoException(const string& msg) : Exception{ msg } {

	}
	*/
};

