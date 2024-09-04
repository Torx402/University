.eqv	ERR_BIN 	-1 # error loading the binary
.eqv	ERR_TPL		-2 # error loading the bitmap template
.eqv	ERR_BMP		-3 # error saving the bitmap result
.eqv	ERR_OP		-4 # error interpretting the opcode

.eqv	PEN		s0	# pen state
.eqv	POS_X		s1	# position.x
.eqv	POS_Y		s2	# position.y
.eqv	DIR_X		s3	# direction.x
.eqv	DIR_Y		s4	# direction.y
.eqv	MVAMT		s5	# movement amount
.eqv	OPCODE		s6 	# opcode value
.eqv	PIXEL		s7 	# pixel address within the bitmap (temp)
.eqv	TPC		s8 	# program buffer offset
.eqv	FILE		s9	# FILE register


.eqv	DSTBITMAP	a0
.eqv	COMMANDS	a1
.eqv	COMMANDSLN	a2
	
.eqv 	BMP_WIDTH	600
.eqv	BMP_HEIGHT	50
.eqv	BMP_STRIDE	1800
.eqv	BMP_PIXELS	54			#minimal header size for 24-bit bmp

.eqv	LEN_BMP		90056
.eqv	LEN_BIN		2048
.eqv 	OP_EOF		-1
.eqv	OP_POS		3
.eqv	OP_DIR		2
.eqv	OP_MOV		1
.eqv	OP_PEN		0

.data
.align 4
res:		.space 	2
bitmap:		.space 	LEN_BMP					#reserves space in memory that is the same size as bmp file
binary:		.space	LEN_BIN					#reserves space in memory for programs
binpath:	.asciz 	"fool.bin"
tplpath:	.asciz 	"tpl.bmp"
rstpath:	.asciz 	"fool.bmp"

inftpl1:	.asciz	"Trying to load the template..."
inftpl2:	.asciz	"OK\n"

infbin1:	.asciz	"Trying to open the program..."
infbin2:	.asciz	"OK!\n\tRunning...\n"
infbin3:	.asciz	"DONE\n"

str_pos:	.asciz 	"Position: "
str_dir:	.asciz 	"Direction: "
str_mov:	.asciz 	"Move: "
str_pen:	.asciz 	"Pen State: "

infbmp1:	.asciz	"Trying to save the result..."
infbmp2:	.asciz	"OK\n"

strmid:		.asciz 	", "		

inferr:		.asciz 	"ERROR\n"				
				# 	00 01 10 11
normal_y:	.word	0, 1, 0, -1				#we create vectors for the direction, where if the bits are 00, that means our direction is to the right, which is 1 on the x-axis, and 0 on the y axis
normal_x:	.word	1, 0, -1, 0

.macro print_str(%addr)
	li		a7, 4
	la		a0, %addr
	ecall
.end_macro

.macro print_int(%value)
	li		a7, 1
	li		a0, %value
	ecall
.end_macro

.macro print_reg(%reg)
	li		a7, 1
	mv		a0, %reg
	ecall
.end_macro

.macro print_char(%value)
	li		a7, 11
	li		a0, %value
	ecall
.end_macro

.macro exit(%code)
	li		a7, 93
	li		a0, %code
	ecall
.end_macro

.macro open(%path, %flags, %handle, %err) #macro to open a file
	li		a7, 1024
	la		a0, %path
	li		a1, %flags
	ecall
	bltz	a0, %err
	mv		%handle, a0
.end_macro	

.macro read(%handle, %addr, %maxlen, %err) #macro to read a file
	li		a7, 63
	mv		a0, %handle
	la		a1, %addr
	li		a2, %maxlen
	ecall
	blez	a0, %err					   #we will jump to appropriate error handling label in case of an error
.end_macro

.macro write(%handle, %addr, %buflen, %err)
	li		a7, 64
	mv		a0, %handle
	la		a1, %addr
	li		a2, %buflen
	ecall
	bne		a0, a2, %err
.end_macro

.macro close(%handle)
	li		a7, 57
	mv		a0, %handle
	ecall
.end_macro

.macro enter()
	addi	sp, sp, -48
	sw		s0, 0(sp)
	sw		s1, 4(sp)
	sw		s2, 8(sp)
	sw		s3, 12(sp)
	sw		s4, 16(sp)
	sw		s5, 20(sp)
	sw		s6, 24(sp)
	sw		s7, 28(sp)
	sw		s8, 32(sp)
	sw		s9, 36(sp)
	sw		s10, 40(sp)
	sw		s11, 44(sp)
.end_macro

.macro leave()
	lw		s0, 0(sp)
	lw		s1, 4(sp)
	lw		s2, 8(sp)
	lw		s3, 12(sp)
	lw		s4, 16(sp)
	lw		s5, 20(sp)
	lw		s6, 24(sp)
	lw		s7, 28(sp)
	lw		s8, 32(sp)
	lw		s9, 36(sp)
	lw		s10, 40(sp)
	lw		s11, 44(sp)
	addi	sp, sp, 48
.end_macro

.text
main:
	# open the template
	print_str(inftpl1)
	open(tplpath, 0, FILE, handle_err_tpl) 		#Opening in read-only mode, we are outputting the file descriptor to FILE (register s0)
	print_str(inftpl2)
	# read the template
	read(FILE, bitmap, LEN_BMP, handle_err_tpl) #read the file with the file descriptor obtained from open macro, and outputs the length read into a0
	close(FILE) #close the file
	
	print_str(infbin1)
	open(binpath, 0, FILE, handle_err_bin) 		#opening the binary file in read-only, saving file descriptor in FILE (s0)
	print_str(infbin2)
	read(FILE, binary, LEN_BIN, handle_err_bin) #read the file with the file descriptor obtained from open macro, and outputs the length read into a0
	mv		FILE, a0							#binary length for turtle function
	close(FILE) # close the file
	
	la		DSTBITMAP, bitmap
	la		COMMANDS, binary
	mv		COMMANDSLN, FILE
	jal		turtle
	
	# open/create the result file
	print_str(infbmp1)
	open(rstpath, 1, FILE, handle_err_bmp)
	print_str(infbmp2)
	# write the result
	write(FILE, bitmap, LEN_BMP, handle_err_bmp)
	close(FILE)
	
	# no error termination
	exit(0)
	
handle_err_bin:
	print_str(inferr)
	exit(ERR_BIN)
handle_err_bmp:
	print_str(inferr)
	exit(ERR_BMP)
handle_err_tpl:
	print_str(inferr)
	exit(ERR_TPL)
handle_err_op:
	print_str(inferr)
	exit(ERR_OP)
	
#extern int turtle(
#	unsigned char *dest_bitmap,
#	unsigned char *commands,
#	unsigned int commands_size
#);
turtle:
	enter()	
	mv		TPC, zero
bin_loop:
	mv		OPCODE, zero
	bge		TPC, COMMANDSLN, bin_done
	add		t0, TPC, COMMANDS
	
	lbu		t1, (t0)
	slli	t1, t1, 8
	lbu		t2, 1(t0)
	addi	TPC, TPC, 2
	or		OPCODE, t1, t2
	
	andi	t0, OPCODE, 3
	
	print_char('[')
	print_reg(t0)
	print_char(']')
	
	li		t1, OP_POS
	beq		t1, t0, handle_pos
	li		t1, OP_DIR
	beq		t1, t0, handle_dir
	li		t1, OP_MOV
	beq		t1, t0, handle_mov
	li		t1, OP_PEN
	beq		t1, t0, handle_pen
	
handle_pos:
	srli	OPCODE, OPCODE, 2		#we shift everything to the right by 2 positions, because we already know what instruction we are working with, this will make extracting the rest of the parameters from the instruction easier
	andi	t0, OPCODE, 63			#we use binary value of 63 (111111) to extract bits 0-5, which now contain our y coordinates
	mv		POS_Y, t0				#we use extracted value and load it into POS_Y (s3)
	mv		OPCODE, zero
	bge		TPC, COMMANDSLN, turtle_error
	add		t0, TPC, COMMANDS
	lbu		t1, (t0)
	slli	t1, t1, 8
	lbu		t2, 1(t0)
	addi	TPC, TPC, 2
	or		OPCODE, t1, t2
	andi	t0, OPCODE, 1023		#we use binary value of 1023 (1111111111) to extract bits 0-9 from our instruction command
	mv		POS_X, t0				#we copy extracted value to POS_X (s2)
	print_str(str_pos)
	print_reg(POS_X)
	print_str(strmid)
	print_reg(POS_Y)
	print_char('\n')
	j		bin_loop
handle_dir:
	srli	OPCODE, OPCODE, 14
	andi	OPCODE, OPCODE, 3
	slli	OPCODE, OPCODE, 2		#multiply by 4 because we are loading words from memory, size is 4, turn it into offset for which we will use with our normal values
	la		t0, normal_x			#load address of normal X values
	add		t0, t0, OPCODE			#increment by the offset
	lw		DIR_X, (t0)				#load the value t0 is pointing to into DIR_X (s4)
	la		t0, normal_y			#load address of normal Y values
	add		t0, t0, OPCODE			#increment by the offset
	lw		DIR_Y, (t0)				#load the value t0 is pointing to into DIR_Y (s5)
	print_str(str_dir)
	print_reg(DIR_X)
	print_str(strmid)
	print_reg(DIR_Y)
	print_char('\n')
	j		bin_loop
handle_mov:
	srli	OPCODE, OPCODE, 6		#at this point we already know we are working with move command, so we shift everything 6 positions to the right in order to make the copying of m0-m9 easier
	andi	MVAMT, OPCODE, 1023 #here, because we have 10 bits, we will andi with 1024-1= 1023 to extract bits m0-m9
	print_str(str_mov)
	print_reg(MVAMT)
	print_char('\n')

draw_loop:								
	blez	MVAMT, draw_done
	blez	POS_X, draw_done		#these check when drawing is done
	blez	POS_Y, draw_done
	li		t0, BMP_WIDTH
	bge		POS_X, t0, draw_done 	#here we check if we are within the boundaries of our bmp file
	li		t0, BMP_HEIGHT
	bge		POS_Y, t0, draw_done	
		
	andi	t0, PEN, 1				#here we check if the pen state is 0, if so, then we move to the loop that draws gaps
	beqz	t0, draw_step
	
	la		PIXEL, bitmap			#we load address of bitmap into PIXEL register (s8)
	addi	PIXEL, PIXEL, BMP_PIXELS #offset of the header
	li		t2, BMP_STRIDE			#this value represents bytes per row
	mul		t1, POS_Y, t2			#multiple y by stride, to get offset of the scan line
	add		PIXEL, PIXEL, t1		#add it to address of pixel buffer
	li		t1, 3					#we multiply by 3 because thats the size of the pixel we want to get within the scan line
	mul		t1, POS_X, t1	
	add		PIXEL, PIXEL, t1		#add it to address of pixel buffer
	
	# blue
	srli	t0, PEN, 1
	andi	t1, t0, 15
	slli	t2, t1, 4				#the color bits consist of 4 bits for each color, and they take up the upper 4 bits of the byte, so we shift left by 4
	sb		t2, 2(PIXEL)
	
	# green
	srli	t0, t0, 4
	andi	t1, t0, 15
	slli	t2, t1, 4
	sb		t2, 1(PIXEL)
	
	# red
	srli	t0, t0, 4
	andi	t1, t0, 15
	slli	t2, t1, 4
	sb		t2, 0(PIXEL)
draw_step:										
	addi	MVAMT, MVAMT, -1
	add		POS_X, POS_X, DIR_X
	add		POS_Y, POS_Y, DIR_Y	
	j		draw_loop
draw_done:
	j		bin_loop
handle_pen:
	srli	PEN, OPCODE, 3
	print_str(str_pen)	
	print_reg(PEN)
	print_char('\n')
	j		bin_loop
bin_done:
	mv		a0, zero
	mv		a1, zero
turtle_leave:
	leave()
	jr		ra
turtle_error:
	li		a0, ERR_OP
	j		turtle_leave
	
