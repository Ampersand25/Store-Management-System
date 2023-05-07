#include "Exception.h"

const string& Exception::getMessage() const noexcept
{
	return msg; // return this->msg;
}