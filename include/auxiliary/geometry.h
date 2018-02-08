#pragma once

template<typename T>
struct point2d {
	T x, y;


	template<typename U>
	inline bool operator== (const point2d<U> &compar) {
		return x == compar.x && y == compar.y;
	}


	template<typename U>
	inline bool operator!= (const point2d<U> &compar) {
		return x != compar.x || y != compar.y;
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


	template<typename U>
	inline void operator-= (const point2d<U> &source) {
		x -= source.x;
		y -= source.y;
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


template<typename T>
void moveVertexArray3d (const T *in, T *out, int count, T dx, T dy, T dz) {
	for (int i = 0; i < count; i++) {
		out[i * 3 + 0] = in[i * 3 + 0] + dx;
		out[i * 3 + 1] = in[i * 3 + 1] + dy;
		out[i * 3 + 2] = in[i * 3 + 2] + dz;
	}
}
