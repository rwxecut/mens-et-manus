#include "Mod.h"


void ModList::load () {
	logger.write_inc ("Scanning for mods...");
	for (auto &dir: fs::directory_iterator (config.path.assets))
		if (fs::is_directory (dir)) {
			fs::path modFilePath = dir.path () / config.path.modfile;
			if (fs::exists (modFilePath)) {
				LuaFile modFile (modFilePath.string ());
				Mod::info_t info = loadModInfo (modFile);
				logger.write ("Mod found: %s %s", info["name"].c_str (), info["version"].c_str ());
				list.emplace_back (info);
			}
		}
	logger.dec_write ("Found %zu mods", list.size ());
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
