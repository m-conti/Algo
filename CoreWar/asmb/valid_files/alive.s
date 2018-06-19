.name "basic_life"
.comment "easy peasy"

start:
	sti r1, %:live, %1
	ld %0, r5

live:
	live %01
	zjmp %:live
