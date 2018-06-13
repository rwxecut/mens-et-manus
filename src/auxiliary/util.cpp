#include "auxiliary/util.h"

namespace gl {
	point2d<GLdouble> unproject (point2d<GLdouble> source) {
		// Load matricies
		GLdouble modelview[16], projection[16];
		GLint viewport[4];
		glGetDoublev (GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev (GL_PROJECTION_MATRIX, projection);
		glGetIntegerv (GL_VIEWPORT, viewport);
		// Unproject
		GLfloat srcZ;
		GLdouble objZ;
		point2d<GLdouble> obj;
		source.y = (GLfloat) (viewport[3] - source.y);
		glReadPixels ((GLint) source.x, (GLint) source.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &srcZ);
		gluUnProject (source.x, source.y, srcZ, modelview, projection, viewport, &obj.x, &obj.y, &objZ);
		return obj;
	}
}
