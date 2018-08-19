#include "Logger.h"
#define CALL_VWRITE {va_list args; va_start (args, fmt); vwrite (fmt, args); va_end (args);}


Logger::Logger (const char *filename) {
	logfile = fopen (filename, "w");
};


Logger::~Logger () {
	write ("Closing log");
	fclose (logfile);
};


void Logger::getDateTime (char *buf, size_t bufsize) {
	time_t now = time (NULL);
	tm *tstruct = localtime (&now);
	strftime (buf, bufsize, "%d-%m-%Y %X", tstruct);
}


void Logger::vwrite (const char *fmt, va_list args) {
	// Print time
	char timestrbuf[32] = {0};
	getDateTime (timestrbuf, sizeof (timestrbuf));
	fprintf (logfile, "%s | ", timestrbuf);
	// Print message
	for (int i = depth; i > 0; i--)
		putc ('\t', logfile);
	vfprintf (logfile, fmt, args);
	fprintf (logfile, "\n");
}


void Logger::write (const char *fmt, ...) {
	CALL_VWRITE
}


void Logger::write_inc (const char *fmt, ...) {
	CALL_VWRITE
	incDepth ();
}


void Logger::write_dec (const char *fmt, ...) {
	CALL_VWRITE
	decDepth ();
}


void Logger::dec_write (const char *fmt, ...) {
	decDepth ();
	CALL_VWRITE
}
