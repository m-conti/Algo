.name "BadAss4Lives"
.comment "Bourrin"

start:
	st r1, :stock
	ld	%589913, r1 #%590053 for the end sort of || 589901
	st	r1, :start
	ldi %:stock, %0, r15
	st r15, :wrte
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
	ld %33685503, r3
	fork %:ld_new_proc
	fork %:u_go_live
	ld %0, r1
	zjmp %:next
	live %01

next:
	ld				%14,r2
	ld %33685503, r4
	ld %34144268, r5
	ld %34144268, r6
	ld %34144268, r6
	ld %34144268, r7
	ld %34144268, r8
	ld %:start, r9
	ld %8740996443, r11
	ld %0, r10
	zjmp %:wrte

u_go_live:
	live %0
	live %0
	live %0
	live %0
	live %0
	ld %18, r2
	ld %4294901760, r3
	ld %4294901760, r4
	ld %0, r1
	zjmp %:wrte

ld_new_proc:
	fork %:stock
	live %0
	live %0
	ld %0, r1
	ld %10, r2
	ld %190055425, r3
	ld %190055425, r4
	ld %190055937, r5
	ld %190056193, r6
	ld %190056449, r7
	ld %190056705, r8
	ld %590099, r9
	ld %0, r1

wrte:
	live %0
	sti r3, r1, r2
