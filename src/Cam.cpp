#include "Cam.h"
#include "Config.h"

#include "lib/glm/vec4.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"


Cam::Cam () {
	moveSpeedMax = config.cam.moveSpeedMax;
	moveAcceleration = config.cam.moveAcceleration;
	zoomSpeed = config.cam.zoomSpeed;
}


void Cam::setup (glm::mat4 *MVP) {
	projection = glm::perspective (glm::radians(FOV), config.screen.aspect, 1.0, renderDistance);
	modelview = glm::lookAt (pos, sight, glm::vec3 (0, 1, 0));
	if (MVP) *MVP = projection * modelview;
}


glm::ivec2 Cam::unproject (const glm::vec2 &source) {
	GLfloat depth;
	GLfloat srcY = config.screen.size.height - source.y;
	glReadPixels ((GLint) source.x, (GLint) srcY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glm::vec3 src (source.x, srcY, depth);
	glm::ivec4 viewport (0, 0, config.screen.size.width, config.screen.size.height);
	glm::vec3 obj = glm::unProject (src, modelview, projection, viewport);
	return glm::ivec2 (obj.x, obj.y);
}


void Cam::accelerate (direction_t *dir) {
	// Accelerate camera if moving
	if (dir->left && (moveSpeed.x >= -moveSpeedMax))
		moveSpeed.x -= 2 * moveAcceleration;
	if (dir->right && (moveSpeed.x <= moveSpeedMax))
		moveSpeed.x += 2 * moveAcceleration;
	if (dir->up && (moveSpeed.y <= moveSpeedMax))
		moveSpeed.y += 2 * moveAcceleration;
	if (dir->down && (moveSpeed.y >= -moveSpeedMax))
		moveSpeed.y -= 2 * moveAcceleration;
}


void Cam::decelerate () {
	// Decelerate camera if stopping moving
	if (moveSpeed.x < 0) moveSpeed.x += moveAcceleration;
	if (moveSpeed.x > 0) moveSpeed.x -= moveAcceleration;
	if (moveSpeed.y < 0) moveSpeed.y += moveAcceleration;
	if (moveSpeed.y > 0) moveSpeed.y -= moveAcceleration;
}


void Cam::move () {
	pos += moveSpeed;
	sight += moveSpeed;
}


void Cam::zoom (int delta) {
	if ((delta > 0 && pos.z < maxZ) || (delta < 0 && pos.z > minZ))
		pos.z += delta * zoomSpeed;
}
