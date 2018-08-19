#pragma once

#include "lib/glad.h"
#include "geometry.h"


namespace gl {
	point2d<GLdouble> unproject (point2d<GLdouble> source);
}
