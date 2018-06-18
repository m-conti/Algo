.name		"My_First"

.comment	"Let's see how he does"

start:
	sti		r1, %:live, %1
	fork %:write
	ld %255, r7
	ld		%0, r5

live:
 	live %01
	zjmp %:live

write:
	ld		%01, r4
	add r1, r10, r3
	st r3, r7
	st r3, r8
	st r3, 10
	st r4, 1
	live %0
	live %0
	live %0
	live %0
	st r3, 500
	st r4, 491
	st r3, r8
	st r3, 625
	st r4, 616
	st r3, 700
	st r4, 791
	st r3, 825
	st r4, 816
	zjmp %6
	fork %50
	ld %0, r6
	zjmp %:write

augm:
live %0
live %0
live %0
live %0
live %0
live %0
live %0
	add r1, r10, r3
	add r7, r7, r7
	add r1, r7, r8
	live %0
	live %0
	live %0
	live %0
	live %0
	live %0
	add r7, r7, r7
	add r1, r7, r8
	live %0
	live %0
	live %0
	live %0
	live %0
	add r7, r7, r7
	add r1, r7, r8
	live %0
	live %0
