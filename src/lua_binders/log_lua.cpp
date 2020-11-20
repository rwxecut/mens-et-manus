#include "lua_binders/log_lua.h"
#include <cstdio>
#include "engine/Logger.h"

namespace lua::bind {

	Log::Log (File *LF) : Bind (LF) {
		// Usertype for game core functions bindings should not be directly used in scripts
		auto log = LF->state.new_usertype<Log> ("__LogBindingType");
		/*---------- Export functions ----------*/
		#define LOG_EXPORT_METHOD(field) BIND_EXPORT_METHOD(log, Log, field)
		LOG_EXPORT_METHOD(write);
		LOG_EXPORT_METHOD(warn);
		LOG_EXPORT_METHOD(fatal);
		#undef LOG_EXPORT_METHOD
	}

	/*---------- Binded functions ----------*/

	void Log::write (const char *msg) {
		logger.write (msg);
	}

	void Log::warn (const char *msg) {
		fprintf (stderr, "%s\n", msg);
		logger.write (msg);
	}

	void Log::fatal (const char *msg) {
		logger.write (msg);
		logger.~Logger ();
		throw std::runtime_error (msg);
	}

}
