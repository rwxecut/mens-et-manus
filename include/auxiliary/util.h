#pragma once

#include <cstdint>
#include <sys/stat.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "geometry.h"

namespace file {
	bool exists (char *fname);
}


namespace gl {
	point2d<GLdouble> unproject (point2d<GLdouble> source);
}
