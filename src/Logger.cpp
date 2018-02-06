#include "Logger.h"


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


void Logger::write (const char *fmt, ...) {
	// Print time
	char timestrbuf[32] = {0};
	getDateTime (timestrbuf, sizeof(timestrbuf));
	fprintf (logfile, "%s | ", timestrbuf);
	// Print message
	va_list args;
	va_start (args, fmt);
	vfprintf (logfile, fmt, args);
	va_end (args);
	fprintf (logfile, "\n");
}
