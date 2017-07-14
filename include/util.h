#pragma once

#include <string>
#include <cstdint>

namespace file {
	bool exists (std::string const &fname);
}

namespace mem {
	// This function allocates a 2D array of type T in a contiguous
	// block of memory, calling the default constructor for each element.
	template<typename T>
	T** new2DArray (uint32_t size_x, uint32_t size_y) {
		T** array = new T*[size_y];
		array[0] = new T[size_x * size_y];
		for (uint32_t y = 1; y < size_y; y++)
			array[y] = array[y-1] + size_x;
		return array;
	}

	// Deletes a 2D array allocated by the previous function.
	template<typename T>
	void delete2DArray (T** array) {
		delete [] array[0];
		delete [] array;
	}
}