#include "Mod.h"


Mod::Mod (std::string const &name, std::string const &version) {
	this->name = name;
	this->version = version;
}


void ModList::load () {
	logger.write ("Scanning for mods...");
	size_t modCount = 0;
	for (auto &dir: fs::directory_iterator (config.path.assets))
		if (fs::is_directory (dir)) {
			fs::path modFilePath = dir.path () / config.path.modfile;
			if (fs::exists (modFilePath)) {
				// mingw does some shit with fs::path.c_str()
				LuaFile modFile (modFilePath.string ().c_str ());
				std::string modName = modFile.state["name"];
				std::string modVersion = modFile.state["version"];
				logger.write ("Mod found: %s %s", modName.c_str (), modVersion.c_str ());
				add (modName, modVersion);
				modCount++;
			}
		}
	logger.write ("Found %zu mods", modCount);
}


void ModList::add (std::string const &name, std::string const &version) {
	list.emplace_back (name, version);
}


void ModList::clear () {
	list.clear ();
}
