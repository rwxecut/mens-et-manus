background = '../assets/thinking.png'
-------------------------------------
package.path = package.path .. ';../lua_utils/?.lua;../cfg/?.lua'
serpent = require('serpent')
utils = require('utils')
config = require('config')
settings = utils.safeRequire('settings', 'settings_default')

--/////////////////////////////////////////////////////////////////////--

function saveSettings ()
	local rs = settings.resolution_selected + 1
	settings.resolution.w = config.resolutions.val[rs].w
	settings.resolution.h = config.resolutions.val[rs].h
	local settingsSerialized = serpent.block(settings, {comment = false, nohuge = true})
	local settingsFile = io.open('../cfg/settings.lua', "w")
	settingsFile:write('return ', settingsSerialized, '\n')
    io.close(settingsFile)
end

settingsWindowVisible = false
function renderSettingsWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Settings', 320, 50, 300, 140, windowFlags) then
		------------------------------
		gui.layout_row_dynamic (30, 2)
		gui.label('Screen resolution', gui.NK_TEXT_LEFT)
		settings.resolution_selected = gui.combo(config.resolutions.str, settings.resolution_selected, 25, 140, 100)
		------------------------------
		gui.layout_row_dynamic (30, 1)
		settings.fullscreen = gui.check_label ('Fullscreen', settings.fullscreen)
		------------------------------
		gui.layout_row_dynamic (30, 2)
		if gui.button_label('Apply') then
            saveSettings()
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

function render ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Main menu', 50, 50, 270, 140, windowFlags) then
		gui.layout_row_dynamic(30, 1)
		-----------------------------
		if gui.button_label('Start game') then
			game.switchRoutine(game.gameRoutine)
		end
		-----------------------------
		if gui.button_label('Settings') then
			settingsWindowVisible = not settingsWindowVisible
		end
		-----------------------------
		if gui.button_label('Exit') then
			game.switchRoutine(game.finalization)
		end
		-----------------------------
		gui.finish()
	end
	if settingsWindowVisible then
		renderSettingsWindow()
	end
end
