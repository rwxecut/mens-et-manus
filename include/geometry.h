#pragma once

template<typename T>
struct point2d {
	T x, y;


	template<typename U>
	inline bool operator== (const point2d<U> &compar) {
		return x == compar.x && y == compar.y;
	}


	template<typename U>
	inline void operator= (const point2d<U> &source) {
		x = source.x;
		y = source.y;
	}


	template<typename U>
	inline void operator+= (const point2d<U> &source) {
		x += source.x;
		y += source.y;
	}
};

#define vector2d point2d


template<typename T>
struct size2d {
	T width, height;
};


template<typename T>
struct point3d {
	T x, y, z;


	template<typename U>
	inline void operator+= (const point2d<U> &source) {
		x += source.x;
		y += source.y;
	}
};

#define vector3d point3d
