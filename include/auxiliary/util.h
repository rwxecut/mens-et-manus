#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "geometry.h"


namespace gl {
	point2d<GLdouble> unproject (point2d<GLdouble> source);
}
