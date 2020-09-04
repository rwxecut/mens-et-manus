package.path = package.path .. ';../lua_utils/?.lua;../cfg/?.lua'
serpent = require('serpent')
utils = require('utils')
config = require('config')
settings = utils.safeRequire('settings', 'settings_default')

--/////////////////////////////////////////////////////////////////////--

background = '../assets/vanilla/mainMenu/thinking.png'
vertShader = '../assets/vanilla/mainMenu/shader.vert'
fragShader = '../assets/vanilla/mainMenu/shader.frag'

modlist = nil
activeWindow = nil

-- Windows positions and widths
function firstWindowBounds(height)
	return {
		x = 50,
		y = 50,
		w = 200,
		h = height
	}
end
function secondWindowBounds(height)
	return {
		x = 250,
		y = 50,
		w = 300,
		h = height
	}
end
function thirdWindowBounds(height)
	return {
		x = 550,
		y = 50,
		w = 200,
		h = height
	}
end

--/////////////////////////////////////////////////////////////////////--

function serverWindow()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Server settings', thirdWindowBounds(200), windowFlags) then
		------------------------------
		gui.layout_row_dynamic(30, 1)
		buffer:create("ip_buf", 16)
		gui:edit_string(gui.NK_EDIT_FIELD, "ip_buf")
		if gui.button_label('Cancel') then
			serverWindowVisible = false
		end
		------------------------------
		gui.finish()
	end
end

function startWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Start game', secondWindowBounds(280), windowFlags) then
		------------------------------
		gui.layout_row_dynamic(20, 1)
		gui.label("Mods:", gui.NK_TEXT_LEFT)
		gui.layout_row_dynamic(74, 1)
		local groupBounds = gui.widget_bounds()
		if gui.group_begin("Mod list", 0) then
			gui.layout_row_dynamic(20, 1)
			for _, mod in pairs(modlist) do
				if mod["selected"] == nil then
					mod["selected"] = false
				end
				local itemBounds = gui.widget_bounds()
				mod["selected"] = gui.selectable_label(mod["name"], gui.NK_TEXT_LEFT, mod["selected"])
				if gui.input_is_mouse_hovering_rect(itemBounds) and gui.input_is_mouse_hovering_rect(groupBounds) then
					gui.tooltip(mod["description"])
				end
			end
			gui.group_end()
		end
		------------------------------
		gui.layout_row_dynamic(30, 1)
		if gui.button_label('Start local game') then
			for _, mod in pairs(modlist) do
				if mod["selected"] then
					-- load mod etc
				end
			end
			game.switchRoutine(game.gameRoutine)
		end
		if gui.button_label('Start server') then
			serverWindowVisible = true
		end
		if gui.button_label('Join server') then
			serverWindowVisible = true
		end
		if gui.button_label('Cancel') then
			serverWindowVisible = false
			activeWindow = nil
		end
		------------------------------
		gui.finish()
	end
	if serverWindowVisible then
		serverWindow()
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

function settingsWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Settings', secondWindowBounds(140), windowFlags) then
		------------------------------
		gui.layout_row_dynamic(30, 1)
		settings.fullscreen = gui.check_label('Fullscreen', settings.fullscreen)
		------------------------------
		if not settings.fullscreen then
			gui.layout_row_dynamic(30, 2)
			gui.label('Screen resolution', gui.NK_TEXT_LEFT)
			settings.resolution_selected = gui.combo(config.resolutions.str, settings.resolution_selected, 25, 140, 100)
		else
			-- empty row
			gui.layout_row_static(30, 0, 0)
		end
		------------------------------
		gui.layout_row_dynamic(30, 2)
		if gui.button_label('Apply') then
			saveSettings()
			game.applySettings()
			activeWindow = nil
		end
		if gui.button_label('Cancel') then
			activeWindow = nil
		end
		------------------------------
		gui.finish()
	end
end

--/////////////////////////////////////////////////////////////////////--

currMod = nil
function modInfoWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE
	if gui.begin(currMod["name"], thirdWindowBounds(170), windowFlags) then
		gui.layout_row_dynamic(0, 1)
		gui.label_wrap("Version: " .. currMod["version"])
		gui.label_wrap("Author: " .. currMod["author"])
		gui.label_wrap("Description: " .. currMod["description"])
		gui.finish()
	end
end

function modWindow()
	local windowFlags = gui.NK_WINDOW_TITLE
	local modInfoWindowVisible = false
	if gui.begin("Mods", secondWindowBounds(170), windowFlags) then
		gui.layout_row_dynamic(20, 1)
		for _, mod in pairs(modlist) do
			local currModSelected = (currMod == mod)
			currModSelected = gui.selectable_label(mod["name"], gui.NK_TEXT_LEFT, currModSelected)
			if currModSelected then
				currMod = mod
			elseif currMod == mod then
				currMod = nil
			end
		end
		modInfoWindowVisible = (currMod ~= nil)
		gui.finish()
	end
	if modInfoWindowVisible then
		modInfoWindow()
	end
end

--/////////////////////////////////////////////////////////////////////--

function mainWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Main menu', firstWindowBounds(170), windowFlags) then
		gui.layout_row_dynamic(30, 1)
		-----------------------------
		if gui.button_label('Start game') then
			activeWindow = startWindow
		end
		-----------------------------
		if gui.button_label('Mods') then
			activeWindow = modWindow
		end
		-----------------------------
		if gui.button_label('Settings') then
			activeWindow = settingsWindow
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
	mainWindow()
	if activeWindow then
		activeWindow()
	end
end

--/////////////////////////////////////////////////////////////////////--

function loadModList()
	modlist = mods:getList()
end
