#pragma once

#include <GL/gl.h>
#include <cstdint>

typedef struct {
	int16_t x, y;
} ipoint;

typedef struct {
	uint16_t x, y;
} upoint;

typedef struct {
	GLdouble x, y;
} dpoint;