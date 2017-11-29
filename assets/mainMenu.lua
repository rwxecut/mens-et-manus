if gui.begin('Sample main menu', 50, 50, 270, 80, gui.NK_WINDOW_TITLE | gui.NK_WINDOW_NO_SCROLLBAR |
	                                              gui.NK_WINDOW_MOVABLE) then
	gui.layout_row_static(30, 250, 1)
	if gui.button_label('UPGRADE') then
		print('Upgrading into game...')
	end
end
gui._end()
