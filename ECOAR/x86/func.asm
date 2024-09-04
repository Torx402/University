bits 32

%define bmp_stride	1800
%define bmp_width 	600
%define bmp_height	50

; note:
; 	comment %define WINDOWS out to switch abi to linux
;	unfortunately, we can't autodetect through 
;	__OUTPUT_FORMAT__,win32
;	because we are building object files beforehand
;%define WINDOWS

; note: 
; 	comment %define DEBUG_PRINTS out to disable
%define DEBUG_PRINTS

%ifdef WINDOWS
global _turtle
extern _debug_pos
extern _debug_dir
extern _debug_mov
extern _debug_pen
%define turtle _turtle
%define debug_pos _debug_pos
%define debug_dir _debug_dir
%define debug_mov _debug_mov
%define debug_pen _debug_pen
%else
global turtle
extern debug_pos
extern debug_dir
extern debug_mov
extern debug_pen
%endif

SECTION .data
align 4

switchito: dd	cmd_setpen, cmd_mkmoves, cmd_setdir, cmd_setpos
directito: dd	1, 0, -1, 0, 0, 1, 0, -1

SECTION .text
align 4

%define dest_bitmap 	ebp+8
%define commands 		ebp+12
%define commands_size 	ebp+16
; stack variables
%define opcode 			ebp-4
%define penstate 		ebp-8
%define movement 		ebp-12
%define position_x 		ebp-16
%define position_y		ebp-20
%define direction_x		ebp-24
%define direction_y 	ebp-28
%define	command_index	ebp-32
%define bitmap_step		ebp-36
%define bitmap_offset	ebp-40

turtle:
	push 	ebp
	mov 	ebp, esp
	sub		esp, 40
	
	mov		[opcode], dword 0
	mov		[penstate], dword 0
	mov		[movement], dword 0
	mov		[position_x], dword 0
	mov		[position_y], dword 0
	mov		[direction_x], dword 0
	mov		[direction_y], dword 0
	mov		[command_index], dword 0
	mov		[bitmap_offset], dword 0
	mov		[bitmap_step], dword 0

cmd_loop:	
	mov		esi, [command_index]
	cmp		esi, [commands_size]
	jge		cmd_done
	
	add		esi, [commands]
	xor		eax, eax
	mov		ah, [esi]
	mov		al, [esi+1]
	mov		[opcode], eax
	add		[command_index], dword 2
	
	and		eax, 3
	shl		eax, 2
	add		eax, switchito
	jmp		[eax]
	
	jmp		cmd_loop
cmd_done:
	xor		eax, eax
turtle_done:
	mov     esp, ebp
	pop		ebp
	ret

; handle set pen state command
cmd_setpen:
	mov		eax, [opcode]
	shr		eax, 3
	mov		[penstate], eax
	; ### DEBUG ###
%ifdef DEBUG_PRINTS
	push	dword [penstate]
	call	debug_pen
	add		esp, 4
%endif
	; ### DEBUG ###
	jmp		cmd_loop
	
; handle movement command
cmd_mkmoves:
	mov		eax, [opcode]
	shr		eax, 6
	and		eax, 1023
	mov		[movement], eax
	
	mov		eax, [direction_y]
	mov		ecx, bmp_stride
	xor		edx, edx
	imul	ecx
	mov		edx, [direction_x]
	lea		edx, [edx+edx*2]
	add		eax, edx
	mov		[bitmap_step], eax
	
	mov		eax, [position_y]
	mov		ecx, bmp_stride
	xor		edx, edx
	mul		ecx
	mov		edx, [position_x]
	lea		edx, [edx+edx*2]
	add		eax, edx
	mov		[bitmap_offset], eax
	
cmd_mkmoves_loop:
	mov		eax, [movement]
	test	eax, eax
	jz		cmd_mkmoves_done
	mov		eax, [position_x]
	cmp		eax, bmp_width
	jge		cmd_mkmoves_done
	cmp		eax, -1
	jle		cmd_mkmoves_done
	mov		eax, [position_y]
	cmp		eax, bmp_height
	jge		cmd_mkmoves_done
	cmp		eax, -1
	jle		cmd_mkmoves_done
	mov		eax, [penstate]
	mov		edx, eax
	and		eax, 1
	test	eax, eax
	jz		cmd_mkmoves_step
cmd_mkmoves_draw:
	mov		eax, [bitmap_offset]
	add		eax, [dest_bitmap]
	shr		edx, 1
	mov		ecx, edx
	and		ecx, 15
	shl		ecx, 4
	mov		[eax], cl
	shr		edx, 4
	mov		ecx, edx
	and		ecx, 15
	shl		ecx, 4
	mov		[eax-1], cl
	shr		edx, 4
	mov		ecx, edx
	and		ecx, 15
	shl		ecx, 4
	mov		[eax-2], cl
	
cmd_mkmoves_step:
	mov		eax, [position_x]
	add		eax, [direction_x]
	mov		[position_x], eax
	mov		eax, [position_y]
	add		eax, [direction_y]
	mov		[position_y], eax
	mov		eax, [bitmap_offset]
	add		eax, [bitmap_step]
	mov		[bitmap_offset], eax
	dec		dword [movement]
	jmp		cmd_mkmoves_loop
cmd_mkmoves_done:
	; ### DEBUG ###
%ifdef DEBUG_PRINTS
	push	dword [movement]
	call	debug_mov
	add		esp, 4
%endif
	; ### DEBUG ###
	jmp		cmd_loop

; handle set direction command
cmd_setdir:
	mov		eax, [opcode]
	shr		eax, 14
	and		eax, 3
	shl		eax, 2
	add		eax, directito
	mov		edx, [eax]
	mov		[direction_x], edx
	mov		edx, [eax+16]
	mov		[direction_y], edx
	; ### DEBUG ###
%ifdef DEBUG_PRINTS
	push	dword [direction_y]
	push	dword [direction_x]
	call	debug_dir
	add		esp, 8
%endif
	; ### DEBUG ###
	jmp		cmd_loop
	
; handle set position command
cmd_setpos:
	mov		eax, [opcode]
	shr		eax, 2
	and		eax, 63
	mov		[position_y], eax
	
	mov		esi, [command_index]
	cmp		esi, [commands_size]
	jge		error_commands_size
	add		esi, [commands]
	xor		eax, eax
	mov		ah, [esi]
	mov		al, [esi+1]
	add		[command_index], dword 2
	
	and		eax, 1023
	mov		[position_x], eax
	
	; ### DEBUG ###
%ifdef DEBUG_PRINTS
	push	dword [position_y]
	push	dword [position_x]
	call	debug_pos
	add		esp, 8
%endif
	; ### DEBUG ###
	jmp		cmd_loop
	
	
; error handler for invalid commands_size
error_commands_size:
	mov		eax, -1
	jmp		turtle_done