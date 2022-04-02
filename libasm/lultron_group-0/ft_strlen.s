segment .text
	global _ft_strlen

_ft_strlen:
	mov		rax, 0

cycle:
	cmp		byte[rdi + rax], 0
	je		exit
	inc		rax
	jmp		cycle

exit:
	ret
