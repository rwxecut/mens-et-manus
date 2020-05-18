#include "Mod.h"
#include "Config.h"
#include "Logger.h"
#include "auxiliary/filesystem.h"


namespace Mod {

	void List::load () {
		logger.write_inc ("Scanning for mods...");
		for (auto &dir: fs::directory_iterator (config.path.assets))
			if (fs::is_directory (dir)) {
				fs::path modFilePath = dir.path () / config.path.modfile;
				if (fs::exists (modFilePath)) {
					lua::File modFile (modFilePath.string ());
					info_t info = loadModInfo (modFile);
					logger.write ("Mod found: %s %s", info["name"].c_str (), info["version"].c_str ());
					list.emplace_back (info);
				}
			}
		logger.dec_write ("Found %zu mods", list.size ());
	}


	info_t List::loadModInfo (lua::File &file) {
		#define GET_INFO(val) {#val, file.state[#val]}
		info_t info = {GET_INFO (name),
		               GET_INFO (version),
		               GET_INFO (author),
		               GET_INFO (description)};
		return info;
		#undef GET_INFO
	}


	void List::clear () {
		list.clear ();
	}

}
