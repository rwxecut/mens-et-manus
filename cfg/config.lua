-- The default game configuration file.

Config = {}

Config.screen = {
	width = 800,
	height = 600
}

Config.cam = {
	moveSpeedMax = 10.0,
	moveAcceleration = 0.5,
	zoomSpeed = 20.0
}

Config.resolutions = {
	str = { '800x600', '1366x768' },
	val = { { w = 800, h = 600 }, { w = 1366, h = 768 } }
}

Config.fpsInterval = 1.5

Config.path = {
	modfile = "mod.lua",
	assets = "../assets",
}
Config.path["splash"] = Config.path.assets .. "/splash.png"
Config.path["mainMenuGUI"] = Config.path.assets .. "/mainMenu.lua"
Config.path["gameMenuGUI"] = Config.path.assets .. "/gameMenu.lua"

return Config
