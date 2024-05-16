#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

static void throwException(const std::string& message)
{
	throw std::runtime_error(message);
}

#endif // EXCEPTION_H