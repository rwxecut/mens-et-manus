#pragma once

#include "lua_binders/bind_lua.h"
#include "Buffer.h"

namespace lua::bind {
	class DataBuffer : public Bind {
	public:
		DataBuffer (File *LF);

	/* Binded functions */
	private:
		bool exists (Buffer::key_t key);
		bool create (Buffer::key_t key, int size);
		void write (Buffer::key_t key, const char* src);
		const char* read (Buffer::key_t key);
	};
}
