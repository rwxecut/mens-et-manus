#pragma once

template<typename T>
struct point2d {
	T x, y;
};
#define vector2d point2d

template<typename T>
struct size2d {
	T width, height;
};

template<typename T>
struct point3d {
	T x, y, z;
};
#define vector3d point3d
