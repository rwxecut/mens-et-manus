#pragma once

#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include "Logger.h"


inline void fatalError (const char *fmt, ...) {
	va_list args, args_cp;
	// Get ms length
	// GCC may change va_list, so we copy it
	va_start (args, fmt);
	va_copy (args_cp, args);
	int msglen = vsnprintf (NULL, 0, fmt, args) + 1;
	va_end (args);
	// Build msg
	char *msg = (char *) calloc ((size_t) msglen, sizeof (char));
	va_start (args_cp, fmt);
	vsnprintf (msg, (size_t) msglen, fmt, args_cp);
	va_end (args_cp);
	// Print and terminate
	logger.write (msg);
	logger.~Logger ();
	throw std::runtime_error (msg);
}
