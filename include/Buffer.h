#pragma once

#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <utility>

class BufferItem {
	std::unique_ptr<char, decltype(&std::free)> data = {nullptr, &std::free};
	size_t data_size = 0;

public:
	BufferItem () = default;
	BufferItem (size_t size) : data_size(size), data((char *) std::calloc (size, 1), &std::free) {}
	inline char* get () { return data.get(); }
	inline const char* safe_get () { return (const char*) data.get(); }
	inline void set (const char* src) { if (data) std::memcpy (data.get(), src, data_size); }
	inline bool ok () { return data != nullptr; }
	inline size_t size () { return data_size; }
};

class Buffer {
public:
	using key_t = const char*;
private:
	std::unordered_map<key_t, BufferItem> data;

public:
	inline bool exists (key_t key) { return data.find (key) != data.end(); }
	inline bool create (key_t key, size_t size) {
		// Should not use data.try_emplace() here
		if (!exists (key)) data.emplace(key, std::move (BufferItem (size)));
		return data[key].ok();
	}
	inline size_t size (key_t key) { return data.at(key).size(); }
	inline void write (key_t key, const char* src) { data.at(key).set (src); }
	inline const char* read (key_t key) { return data.at(key).safe_get(); }
	inline char* get (key_t key) { return data.at(key).get(); }
};
