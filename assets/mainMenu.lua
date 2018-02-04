if gui.begin('Sample main menu', 50, 50, 270, 110, gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR |
	                                               gui.NK_WINDOW_MOVABLE) then
	gui.layout_row_dynamic(30, 1)
	if gui.button_label('Start game') then
		game.switchRoutine(game.gameRoutine)
	end
	if gui.button_label('Exit') then
		game.switchRoutine(game.finalization)
	end
end
gui.finish()
