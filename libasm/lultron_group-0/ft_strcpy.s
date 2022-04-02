segment .text
	global _ft_strcpy

_ft_strcpy:
	mov	rcx, 0

cycle:
	cmp	byte[rsi + rcx], 0
	je	exit
	mov	al, byte[rsi + rcx]
	mov	byte[rdi + rcx], al
	inc	rcx
	jmp	cycle

exit:
	mov	byte[rdi + rcx], 0
	mov	rax, rdi
	ret
