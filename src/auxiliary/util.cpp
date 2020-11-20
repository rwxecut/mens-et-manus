#include "auxiliary/util.h"

#include <fstream>
#include "engine/Logger.h"
#include "auxiliary/errors.h"


std::string loadFileToString (const char *filename, bool &success) {
	std::ifstream file (filename, std::ios::in | std::ios::binary);
	std::string string;
	if (file) {
		success = true;
		file.seekg (0, std::ios::end);
		string.resize ((unsigned) file.tellg ());
		file.seekg (0, std::ios::beg);
		file.read (&string[0], string.size ());
		file.close ();
		logger.write ("File loaded: %s", filename);
	} else {
		warnError ("Error loading file: %s", filename);
		success = false;
	}
	return string;
}
