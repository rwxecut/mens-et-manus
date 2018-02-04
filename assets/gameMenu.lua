if gui.begin('Sample game GUI', 50, 50, 270, 80, gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR |
	                                             gui.NK_WINDOW_MOVABLE) then
	gui.layout_row_dynamic(30, 1)
	if gui.button_label('Back to menu') then
		game.switchRoutine(game.mainMenuRoutine)
	end
end
gui.finish()
