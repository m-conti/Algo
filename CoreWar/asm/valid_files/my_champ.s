.name "Test 02"
.comment "Some understanding"

begin_coromp2:
	st				r1, :stock
	ld				%151068160,r1
	st				r1, :begin_coromp2
	ld				%506,r2
	ld				%100,r3
	live			%0
	fork            %:corruption_second2

corruption_first2:
	ld				%34144757,r4
	st				r4,r5
	ld				%50921567,r6
	st				r6,r7
	st				r6,r12
	st				r6,r13
	st				r6,r14
	st				r6,r15
	st				r4,r8
	st				r4,r9
	st				r4,r10
	ld				%167685120,r11
	ld				%4,r1
	sub             r16, r16, r16
	zjmp            %:end2

corruption_second2:
	ld		%190055681,r4
	ld		%190055937,r5
	ld		%190057473,r6
	ld		%190057729,r12
	ld		%190057985,r13
	ld		%190058241,r14
	ld		%190056193,r15
	ld		%190056449,r7
	ld		%190056705,r8
	ld		%190056961,r9
	ld		%151087617,r10
	ld		%151035392,r11
	ld		%0, r1

	zjmp	%:end2
	live	%0
	live	%0
	live	%0
	live	%0
	live	%0
	live	%0
	aff		r2

stock:
	aff		r2
	live	%0
	live	%0
	live	%0

end2:
	sti		r4,r1,%505
	zjmp	%499
