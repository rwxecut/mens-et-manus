#include "Mod.h"


void ModList::load () {
	logger.write ("Scanning for mods...");
	for (auto &dir: fs::directory_iterator (config.path.assets))
		if (fs::is_directory (dir)) {
			fs::path modFilePath = dir.path () / config.path.modfile;
			if (fs::exists (modFilePath)) {
				// mingw does some shit with fs::path.c_str()
				LuaFile modFile (modFilePath.string ().c_str ());
				Mod::info_t info = loadModInfo (modFile);
				logger.write ("Mod found: %s %s", info["name"].c_str (), info["version"].c_str ());
				list.emplace_back (info);
			}
		}
	logger.write ("Found %zu mods", list.size ());
}


Mod::info_t ModList::loadModInfo (LuaFile &file) {
	#define GET_INFO(val) {#val, file.state[#val]}
	Mod::info_t info = {GET_INFO (name),
	                    GET_INFO (version),
	                    GET_INFO (author),
	                    GET_INFO (description)};
	return info;
	#undef GET_INFO
}


void ModList::clear () {
	list.clear ();
}
