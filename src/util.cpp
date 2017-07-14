#include "util.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <sys/stat.h>

namespace file {
	bool exists (std::string const &fname) {
		struct stat buffer;
		return (stat (fname.c_str (), &buffer) == 0);
	}
}