package.path = package.path .. ';../lua_utils/?.lua;../cfg/?.lua'
serpent = require('serpent')
utils = require('utils')
config = require('config')
settings = utils.safeRequire('settings', 'settings_default')

--/////////////////////////////////////////////////////////////////////--
background = '../assets/thinking.png'
secondWindowX = 250

startWindowVisible = false
function renderStartWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Start game', secondWindowX, 50, 300, 170, windowFlags) then
		------------------------------
		gui.layout_row_dynamic(20, 1)
		gui.label("Mods: [UNDER CONSTRUCTION]", gui.NK_TEXT_LEFT)
		gui.layout_row_dynamic(74, 1);
		------------------------------
		gui.layout_row_dynamic(30, 2)
		if gui.button_label('Start') then
			game.switchRoutine(game.gameRoutine)
		end
		if gui.button_label('Cancel') then
			startWindowVisible = false
		end
		------------------------------
		gui.finish()
	end
end

--/////////////////////////////////////////////////////////////////////--

function saveSettings ()
	if settings.fullscreen then
		settings.resolution.w, settings.resolution.h = game.getScreenResolution()
	else
		local rs = settings.resolution_selected + 1
		settings.resolution.w = config.resolutions.val[rs].w
		settings.resolution.h = config.resolutions.val[rs].h
	end
	local settingsSerialized = serpent.block(settings, { comment = false, nohuge = true })
	local settingsFile = io.open('../cfg/settings.lua', "w")
	settingsFile:write('Settings = ', settingsSerialized, '\nreturn Settings\n')
	io.close(settingsFile)
end

settingsWindowVisible = false
function renderSettingsWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Settings', secondWindowX, 50, 300, 140, windowFlags) then
		------------------------------
		gui.layout_row_dynamic(30, 1)
		settings.fullscreen = gui.check_label('Fullscreen', settings.fullscreen)
		------------------------------
		if not settings.fullscreen then
			gui.layout_row_dynamic(30, 2)
			gui.label('Screen resolution', gui.NK_TEXT_LEFT)
			settings.resolution_selected = gui.combo(config.resolutions.str, settings.resolution_selected, 25, 140, 100)
		else -- empty row
			gui.layout_row_static (30, 0, 0)
		end
		------------------------------
		gui.layout_row_dynamic(30, 2)
		if gui.button_label('Apply') then
			saveSettings()
			game.applySettings()
			settingsWindowVisible = false
		end
		if gui.button_label('Cancel') then
			settingsWindowVisible = false
		end
		------------------------------
		gui.finish()
	end
end

--/////////////////////////////////////////////////////////////////////--

function renderMainWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Main menu', 50, 50, 200, 170, windowFlags) then
		gui.layout_row_dynamic(30, 1)
		-----------------------------
		if gui.button_label('Start game') then
			startWindowVisible = not startWindowVisible
			settingsWindowVisible = false
		end
		-----------------------------
		if gui.button_label('Mods') then
			startWindowVisible = false
			settingsWindowVisible = false
			local modlist = mods.getList()
			local modlistStr = serpent.block(modlist, { comment = false, nohuge = true })
			print(modlistStr)
		end
		-----------------------------
		if gui.button_label('Settings') then
			startWindowVisible = false
			settingsWindowVisible = not settingsWindowVisible
		end
		-----------------------------
		if gui.button_label('Exit') then
			game.switchRoutine(game.finalization)
		end
		-----------------------------
		gui.finish()
	end
end

--/////////////////////////////////////////////////////////////////////--

function render ()
	renderMainWindow()
	if startWindowVisible then
		renderStartWindow()
	end
	if settingsWindowVisible then
		renderSettingsWindow()
	end
end
