.global on_key_pressed_start
.type on_key_pressed_start, @function
on_key_pressed_start:
	pushal
	call on_key_pressed
	popal
	iret

.global ignore_start
.type ignore_start, @function
ignore_start:
	pushal
	call ignore
	popal
	iret
