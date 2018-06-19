.name "BadAss4Lives"
.comment "
This is a multi line comment
To prove it works
"

start:
	st r1, :stock
	ld	%589913, r1 #%590053 for the end sort of || 589901
	st	r1, :start
	ldi %:stock, %0, r15
	st r15, :second_write
	ld %01, r2
	live %0
	fork %:prep
	ld %0, r3

	aff r1
stock:
	live %0
	zjmp %-6

prep:
	ld %499, r13
	ld %34144755, r3
	fork %:ld_new_proc
	ld %0, r1
	zjmp %:next
	live %01

second_write:
	live %0
	ld %250, r12
	add r2, r12, r2
	ld %0, r1
	zjmp %:wrte

next:
	ld				%510,r2
	ld %34144755, r4
	ld %34144755, r5
	ld %34144755, r6
	ld %34144755, r6
	ld %34144755, r7
	ld %34144755, r8
	ld %:start, r9
	ld %8740996443, r11
	ld %0, r10
	zjmp %:wrte

ld_new_proc:
	live %0
	live %0
	ld %0, r1
	ld %506, r2
	ld %190055425, r3
	ld %190055681, r4
	ld %190055937, r5
	ld %190056193, r6
	ld %190056449, r7
	ld %190056705, r8
	ld %590099, r9
	ld %0, r1

wrte:
	sti r3, r1, r2
	zjmp %499

end:
	live %0
