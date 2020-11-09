#pragma once

#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <cstdint>


class Logger {
	FILE *logfile;
	uint8_t depth = 0;

	static void getDateTime (char *buf, size_t bufsize);

public:
	Logger (const char *filename);
	~Logger ();

	inline void incDepth () { depth++; }
	inline void decDepth () { depth--; }

	void vwrite (const char *fmt, va_list args);
	void write (const char *fmt, ...);
	void write_inc (const char *fmt, ...); // print and increase depth
	void write_dec (const char *fmt, ...); // print and decrease depth
	void dec_write (const char *fmt, ...); // decrease depth and print
};

#ifndef LOG_IMPLEMENT
extern Logger logger;
#endif
