section .text
	global _ft_read
	extern ___error

_ft_read:
	mov		rax, 0x2000003
	syscall
	jc		err
	ret

err:
	push	rdx
	mov		rdx, rax
	call	___error
	mov		[rax], rdx
	pop		rdx
	mov		rax, -1
	ret