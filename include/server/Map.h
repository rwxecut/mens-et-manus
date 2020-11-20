#pragma once

#include "lib/glad.h"
#include <cstdint>
#include "server/Tile.h"
#include "client/Shader.h"
#include "client/Cam.h"
#include "client/Texture.h"
#include "auxiliary/geometry.h"
#include "auxiliary/primitives.h"

#include "lib/glm/vec2.hpp"
#include "lib/glm/mat4x4.hpp"


class Map {
	friend class Game;
	Cam *cam;

	Tile *tilesMem;
	Tile **tiles;
	size2d<uint16_t> size;

	static constexpr int mouseMoveArea = 40;

	Texture *grassTex;
	ShaderProgramPtr tileShader;
	gl::HexPtr tileHex;

	void draw (glm::mat4 MVP);
	static glm::ivec2 getHoveredTile (glm::vec2 point);
	void setSelectedTile (glm::ivec2 mousePos);
	void setVisibleTiles (glm::ivec2 winSize);

public:
	Map (Cam *cam);
	~Map ();
};
