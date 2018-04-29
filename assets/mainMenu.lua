background = '../assets/thinking.png'
-------------------------------------


optionsVisible = false
resolutions = '640x480|1366x768|4K Ultra HD'
selectedResolution = 0
fullscreen = 0
function renderOptions ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Options', 320, 50, 300, 140, windowFlags) then
		gui.layout_row_dynamic (30, 2)
		gui.label('Screen resolution', gui.NK_TEXT_LEFT)
		selectedResolution = gui.combo_separator(resolutions, string.byte('|'), selectedResolution, 3, 25, 140, 100)
		gui.layout_row_dynamic (30, 1)
		fullscreen = gui.check_label ('Fullscreen', fullscreen)
		gui.layout_row_dynamic (30, 2)
		if gui.button_label('Apply') then
			optionsVisible = false
		end
		if gui.button_label('Cancel') then
			optionsVisible = false
		end
		gui.finish()
	end
end


function render ()
	local windowFlags = gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR
	if gui.begin('Main menu', 50, 50, 270, 140, windowFlags) then
		gui.layout_row_dynamic(30, 1)
		if gui.button_label('Start game') then
			game.switchRoutine(game.gameRoutine)
		end
		if gui.button_label('Options') then
			optionsVisible = not optionsVisible
		end
		if gui.button_label('Exit') then
			game.switchRoutine(game.finalization)
		end
		gui.finish()
	end
	if optionsVisible then
		renderOptions ()
	end
end
