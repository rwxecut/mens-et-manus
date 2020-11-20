#pragma once

#include "lib/glad.h"
#include "auxiliary/geometry.h"
#include <string>


namespace gl {
	inline GLsizei sizef (int n) { return n * sizeof (GLfloat); }
	inline GLvoid *psizef (int n) { return (GLvoid *) (n * sizeof (GLfloat)); }
}


std::string loadFileToString (const char *filename, bool &success);
