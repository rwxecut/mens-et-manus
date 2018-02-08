#pragma once

#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include "Logger.h"


inline void fatalError (const char *fmt, ...) {
	va_list args;
	char msg[256] = {0};
	va_start (args, fmt);
	vsnprintf (msg, sizeof (msg), fmt, args);
	va_end (args);
	logger.write (msg);
	logger.~Logger ();
	throw std::runtime_error (msg);
}
