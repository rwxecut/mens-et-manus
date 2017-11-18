if gui.begin('Sample Tsundere GUI', 50, 50, 300, 100) then
	gui.layout_row_static(30, 250, 1)
	if gui.button_label('Don\'t touch me too hard...') then
		print('S-S-Sempai... B-baka!!')
	end
end
gui._end()
