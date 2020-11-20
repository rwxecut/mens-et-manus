#pragma once

#include "lib/glad.h"
#include <cstdint>
#include "client/Shader.h"
#include "client/Texture.h"
#include "auxiliary/geometry.h"
#include "auxiliary/primitives.h"

#include "lib/glm/vec2.hpp"

class Tile {
	friend class Map;

	Texture *tex;

	static constexpr GLfloat hex_l = 100.0f;
	static constexpr GLfloat hex_r = 0.866f * hex_l;

	static const GLfloat hexVertex[24];

public:
	glm::ivec2 pos;

	static glm::ivec2 selected;
	static glm::ivec2 visBottomLeft, visTopRight;

	Tile (glm::ivec2 pos, Texture *tex);
	void draw (ShaderProgram &shader, gl::Hex &hex);
};
