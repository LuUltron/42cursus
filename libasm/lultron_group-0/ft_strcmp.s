section.text:
	global _ft_strcmp

_ft_strcmp:
	mov		rax, 0

cycle:
	mov		cl, byte[rsi + rax]
	mov		dl, byte[rdi + rax]
	cmp		byte[rsi + rax], 0
	je		exit
	cmp		byte[rdi + rax], 0
	je		exit
	cmp		cl, dl
	jne		exit
	inc		rax
	jmp		cycle

exit:
	movzx	rax, dl
	movzx	rdx, cl
	sub		rax, rdx
	ret