#include "server/Map.h"
#include <cstdlib>
#include <cmath>
#include <new>


Map::Map (Cam *cam) {
	this->cam = cam;

	const char *vertShaderPath = "../assets/vanilla/tiles/shaders/shader.vert";
	const char *fragShaderPath = "../assets/vanilla/tiles/shaders/shader.frag";
	tileShader = std::make_unique<ShaderProgram> ("Tile", Shader::fromFile, vertShaderPath,
			Shader::fromFile, fragShaderPath);

	grassTex = new Texture ("../assets/vanilla/tiles/grass.png");
	size = {20, 10}; // temp
	tiles = (Tile **) calloc (size.height, sizeof (Tile *));
	tilesMem = (Tile *) calloc (size.width * size.height, sizeof (Tile));
	for (uint16_t y = 0; y < size.height; y++) {
		tiles[y] = tilesMem + y * size.width;
		for (uint16_t x = 0; x < size.width; x++)
			new (&tiles[y][x]) Tile ({x, y}, grassTex);
	}

	tileHex = std::make_unique<gl::Hex> (GL_STATIC_DRAW, Tile::hexVertex, sizeof (Tile::hexVertex));
	tileHex->setAttributes (0, 2, 4, 0); // X, Y
	tileHex->setAttributes (1, 2, 4, 2); // S, T
}


Map::~Map () {
	free (tiles);
	free (tilesMem);
	delete grassTex;
}


void Map::draw (glm::mat4 MVP) {
	glEnable (GL_DEPTH_TEST);

	// Draw visible tiles
	tileShader->use ();
	tileShader->setUniform ("MVP", MVP);
	glLineWidth (2.0);
	//for (int16_t y = Tile::visBottomLeft.y; y <= Tile::visTopRight.y; y++)
	//	for (int16_t x = Tile::visBottomLeft.x; x <= Tile::visTopRight.x; x++)
	for (int16_t y = 0; y < size.height; y++)
		for (int16_t x = 0; x < size.width; x++)
			tiles[y][x].draw (*tileShader, *tileHex);
}


void Map::setSelectedTile (glm::ivec2 mousePos) {
	glm::ivec2 unprojection = cam->unproject (mousePos);
	Tile::selected = getHoveredTile (unprojection);
}


void Map::setVisibleTiles (glm::ivec2 winSize) {
	Tile::visBottomLeft = getHoveredTile (cam->unproject (glm::ivec2 (0, winSize.y)));
	Tile::visTopRight = getHoveredTile (cam->unproject (glm::ivec2 (winSize.x, 0)));
	// Extend range
	const int exRange = 1;
	glm::ivec2 exVector (exRange, exRange);
	Tile::visBottomLeft -= exVector;
	Tile::visTopRight += exVector;
	// Crop to bounds
	if (Tile::visBottomLeft.x < 0) Tile::visBottomLeft.x = 0;
	if (Tile::visBottomLeft.y < 0) Tile::visBottomLeft.y = 0;
	if (Tile::visTopRight.x >= size.width) Tile::visTopRight.x = (int16_t) (size.width - 1);
	if (Tile::visTopRight.y >= size.height) Tile::visTopRight.y = (int16_t) (size.height - 1);
}


glm::ivec2 Map::getHoveredTile (glm::vec2 point) {
	struct {
		int16_t x; // Coordinates of centers
		int16_t y; // of the two nearest tiles
		GLdouble dist; // Distance from point to tile center
	} tCntr[2];

	// Coordinates of the point in the tiles coordinate system
	GLdouble x_hex = point.x / Tile::hex_r;
	GLdouble y_hex = point.y / (Tile::hex_l * 3 / 2);

	// Choose two nearest tiles
	int16_t y_floor = (int16_t) std::floor (y_hex);
	tCntr[0].x = (int16_t) std::floor (x_hex);
	tCntr[1].x = (int16_t) std::ceil (x_hex);
	bool parity = (tCntr[0].x & 1) == (y_floor & 1);
	tCntr[parity].y = (int16_t) std::ceil (y_hex);
	tCntr[!parity].y = y_floor;

	// Calculate distance to tile centers
	for (int i = 0; i <= 1; i++) {
		GLdouble dist_x = point.x - tCntr[i].x * Tile::hex_r;
		GLdouble dist_y = point.y - tCntr[i].y * Tile::hex_l * 3 / 2;
		tCntr[i].dist = std::sqrt (dist_x * dist_x + dist_y * dist_y);
	}

	// Return the nearest tile center
	int nearest = tCntr[0].dist >= tCntr[1].dist;
	tCntr[nearest].x >>= 1;
	return glm::ivec2 (tCntr[nearest].x, tCntr[nearest].y);
}
