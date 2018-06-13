#pragma once

#include <string>
#include <vector>
#include "Config.h"
#include "auxiliary/filesystem.h"


class Mod {
public:
	std::string name, version;

	Mod (std::string const &name, std::string const &version);
};


class ModList {
public:
	std::vector<Mod> list;

	void load ();
	void add (std::string const &name, std::string const &version);
	void clear ();
};
