#pragma once

#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include "Logger.h"


#define __CALL_ERR_VWRITE {va_list args; va_start (args, fmt); msg = __err::vwrite (fmt, args); va_end (args);}


namespace __err {
	inline char *vwrite (const char *fmt, va_list args) {
		va_list args_cp;
		// Get message length
		// GCC may change va_list, so we copy it
		va_copy (args_cp, args);
		int msglen = vsnprintf (NULL, 0, fmt, args) + 1;
		// Build msg
		char *msg = (char *) calloc ((size_t) msglen, sizeof (char));
		vsnprintf (msg, (size_t) msglen, fmt, args_cp);
		return msg;
	};
}


inline void warnError (const char *fmt, ...) {
	char *msg = NULL;
	__CALL_ERR_VWRITE;
	fprintf (stderr, "%s\n", msg);
	logger.write (msg);
	free (msg);
}


inline void fatalError (const char *fmt, ...) {
	char *msg = NULL;
	__CALL_ERR_VWRITE;
	logger.write (msg);
	free (msg);
	logger.~Logger ();
	throw std::runtime_error (msg);
}
