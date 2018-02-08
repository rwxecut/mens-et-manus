#pragma once

#include <cstdio>
#include <cstdarg>
#include <ctime>


class Logger {
	FILE *logfile;

	void getDateTime (char *buf, size_t bufsize);

public:
	Logger (const char *filename);
	~Logger ();

	void vwrite (const char *fmt, va_list args);
	void write (const char *fmt, ...);
};

#ifndef LOG_IMPLEMENT
extern Logger logger;
#endif
