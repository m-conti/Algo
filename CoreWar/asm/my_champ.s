.name		"My_First"

.comment	"Let's see how he does"

start:
	st		r1, 55
	live	%01
	fork %105

live: live %02
	zjmp %:live
