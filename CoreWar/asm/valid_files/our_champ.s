.name "BadAss4Lives"
.comment "
This is a multi line comment
To prove it works
"

start:
	st r1, :stock
	ld	%590053, r1
	st	r1, :start
	ldi %:stock, %0, r15
	ld %01, r2
	sti r15, :end, %1
	live %0
	fork %:prep
	ld %0, r3

	aff r1
stock:
	live %0
	zjmp %-6

prep:
	ld %0, r1
	ld %34144755, r3
	fork %:ld_new_proc

next:
	ld				%510,r2
	ld %34144755, r4
	ld %34144755, r5
	ld %34144755, r6
	ld %34144755, r6
	ld %34144755, r7
	ld %34144755, r8
	ld %0, r9
	ld %8740996443, r11
	ld %0, r10
	zjmp %:wrte

ld_new_proc:
	ld %0, r1
	ld %506, r2
	ld %190055425, r3
	ld %190055681, r4
	ld %190055937, r5
	ld %190056193, r6
	ld %190056449, r7
	ld %190056705, r8
	ld %590145, r9
	ld %0, r1

wrte:
	sti r3, r1, r2
	zjmp %499

end:
	live %0
