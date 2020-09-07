#include "lua_binders/buffer_lua.h"

namespace lua::bind {

	DataBuffer::DataBuffer (File *LF) : Bind (LF) {
		// Usertype for buffer functions bindings should not be directly used in scripts
		auto db = LF->state.new_usertype<DataBuffer> ("__DataBufferBindingType");
		/*---------- Export functions ----------*/
		#define DB_EXPORT_METHOD(field) {db[#field] = &DataBuffer::field;}
		DB_EXPORT_METHOD (exists);
		DB_EXPORT_METHOD (create);
		DB_EXPORT_METHOD (write);
		DB_EXPORT_METHOD (read);
	}

	/*---------- Binded functions ----------*/

	bool DataBuffer::exists (Buffer::key_t key) {
		return LF->buffer.exists (key);
	}

	bool DataBuffer::create (Buffer::key_t key, int size) {
		return LF->buffer.create (key, size);
	}

	void DataBuffer::write (Buffer::key_t key, const char *src) {
		LF->buffer.write (key, src);
	}

	const char* DataBuffer::read (Buffer::key_t key) {
		return LF->buffer.read (key);
	}

}
