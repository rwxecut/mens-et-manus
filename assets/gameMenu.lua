if gui.begin('Sample game GUI', 50, 50, 270, 80, gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR |
	                                             gui.NK_WINDOW_MOVABLE) then
	gui.layout_row_static(30, 250, 1)
	if gui.button_label('HECK GO BACK') then
		print('Going back...')
		game.switchRoutine(game.mainMenuRoutine)
	end
end
gui._end()
