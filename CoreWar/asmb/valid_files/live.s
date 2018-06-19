.name		"zdoh"
.comment	"w8 for da next one"

lol:	st		r1, :wall
	ld 0, r5
	st r5, :live
	and		r3, %0, r3

jmp:	fork		%:start
ld		0, r4
st		r4, -6
zjmp		%:jmp

start:	live		%0
live		%42
fork		%:live

live:
live	%1
fork	%:wall
fork	%:live

wall:	live	%42
st      r8,-400
zjmp	%:wall
