#include "auxiliary/primitives.h"

namespace gl {

	/* GL_TRIANGLE_FAN
	 * 0--3
	 * |\ |
	 * | \|
	 * 1--2
	 */
	const GLuint Rect::indices[4] = {0, 1, 2, 3};

	/* GL_TRIANGLE_FAN
	 *     /0\
	 *   / /|\ \
	 * 1  / | \  5
	 * | /  |  \ |
	 * 2    |    4
	 *   \  |  /
	 *     \3/
	 *
	 * GL_LINE_LOOP
	 *     /0\
	 *   /     \
	 * 1         5
	 * |         |
	 * 2         4
	 *   \     /
	 *     \3/
	 */
	const GLuint Hex::indices[6] = {0, 1, 2, 3, 4, 5};

}
