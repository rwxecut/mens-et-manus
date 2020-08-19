#pragma once

#include <cstdlib>
#include <cstring>
#include <unordered_map>

namespace lua {

	class BufferItem {
		char* data = nullptr;
		size_t data_size = 0;

	public:
		BufferItem () = delete;
		BufferItem (size_t size) : data_size(size) { data = (char*) std::calloc (size, 1); }
		~BufferItem () { std::free (data); }
		inline char* get () { return data; }
		inline const char* safe_get () { return (const char*) data; }
		inline void set (const char* src) { if (data) std::memcpy (data, src, data_size); }
		inline bool ok () { return data != nullptr; }
	};

	class Buffer {
		using key_t = const char*;
		std::unordered_map<key_t, BufferItem> data;

	public:
		inline bool exists (key_t key) { return data.find (key) != data.end(); }
		inline bool create (key_t key, size_t size) {
			if (!exists (key)) data[key] = BufferItem (size);
			return data[key].ok();
		}
		inline void write (key_t key, const char* src) { data.at(key).set (src); }
		inline const char* read (key_t key) { return data.at(key).safe_get(); }
		inline char* get (key_t key) { return data.at(key).get(); }
	};

}
