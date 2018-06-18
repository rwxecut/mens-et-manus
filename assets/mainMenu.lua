package.path = package.path .. ';../lua_utils/?.lua;../cfg/?.lua'
serpent = require('serpent')
utils = require('utils')
config = require('config')
settings = utils.safeRequire('settings', 'settings_default')

--/////////////////////////////////////////////////////////////////////--

background = '../assets/thinking.png'
modlist = nil

-- Windows positions and widths
windowY = 50
firstWindowX = 50
firstWindowW = 200
secondWindowX = firstWindowX + firstWindowW
secondWindowW = 300
thirdWindowX = secondWindowX + secondWindowW
thirdWindowW = 200

--/////////////////////////////////////////////////////////////////////--

startWindowVisible = false
function renderStartWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Start game', secondWindowX, windowY, secondWindowW, 170, windowFlags) then
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
		gui.layout_row_dynamic(30, 2)
		if gui.button_label('Start') then
			for _, mod in pairs(modlist) do
				if mod["selected"] then
					-- load mod etc
				end
			end
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
	if gui.begin('Settings', secondWindowX, windowY, secondWindowW, 140, windowFlags) then
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

modInfoWindowVisible = false
currMod = nil
function renderModInfoWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE
	if gui.begin(currMod["name"], thirdWindowX, windowY, thirdWindowW, 170, windowFlags) then
		gui.layout_row_dynamic(0, 1)
		gui.label_wrap("Version: " .. currMod["version"])
		gui.label_wrap("Author: " .. currMod["author"])
		gui.label_wrap("Description: " .. currMod["description"])
		gui.finish()
	end
end

modWindowVisible = false
function renderModWindow()
	local windowFlags = gui.NK_WINDOW_TITLE
	if gui.begin("Mods", secondWindowX, windowY, secondWindowW, 170, windowFlags) then
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
end

--/////////////////////////////////////////////////////////////////////--

function renderMainWindow ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Main menu', firstWindowX, windowY, firstWindowW, 170, windowFlags) then
		gui.layout_row_dynamic(30, 1)
		-----------------------------
		if gui.button_label('Start game') then
			startWindowVisible = not startWindowVisible
			settingsWindowVisible = false
			modWindowVisible = false
			modInfoWindowVisible = false
		end
		-----------------------------
		if gui.button_label('Mods') then
			startWindowVisible = false
			settingsWindowVisible = false
			modWindowVisible = not modWindowVisible
			modInfoWindowVisible = false
		end
		-----------------------------
		if gui.button_label('Settings') then
			startWindowVisible = false
			settingsWindowVisible = not settingsWindowVisible
			modWindowVisible = false
			modInfoWindowVisible = false
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
	if modWindowVisible then
		renderModWindow()
	end
	if modInfoWindowVisible then
		renderModInfoWindow()
	end
end

--/////////////////////////////////////////////////////////////////////--

function loadModList()
	modlist = mods.getList()
end
