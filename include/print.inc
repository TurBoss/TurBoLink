
;       Subroutine      Print 8-bit hexidecimal number
;       Inputs          A - number to be printed - 0ABh
;       Outputs         ________________________
PRINT_HEX:
	push	af
	push	bc
	push	de
	call	__NUMTOHEX
	ld		a,	d
	call	VDP_CHPUT
	ld		a,	e
	call	VDP_CHPUT
	pop		de
	pop		bc
	pop		af
	ret

SER_PRINT_HEX:
	push	af
	push	bc
	push	de
	call	__NUMTOHEX
	ld		a,	d
	call	SER_CHPUT
	ld		a,	e
	call	SER_CHPUT
	pop		de
	pop		bc
	pop		af
	ret

SER_PRINT_HEX_4:
	push	af

	push	bc
	push	de


	call	__NUMTOHEX

	ld		a,	d
	call	SER_CHPUT
	ld		a,	e
	call	SER_CHPUT

	pop		de
	pop		bc

	pop		af

	ret


;       Subroutine      Convert 8-bit hexidecimal number to ASCII reprentation
;       Inputs          A - number to be printed - 0ABh
;       Outputs         DE - two byte ASCII values - D=65 / 'A' and E=66 / 'B'

__NUMTOHEX:

        ld c, a   ; a = number to convert
        call _NTH1
        ld d, a
        ld a, c
        call _NTH2
        ld e, a
        ret  ; return with hex number in de

_NTH1:

        rra
        rra
        rra
        rra

_NTH2:

        or 0F0h
        daa
        add a, 0A0h
        adc a, 040h ; Ascii hex at this point (0 to F)   
        ret


;       Subroutine      Print a buffer of data in HEX
;       Inputs          HL - buffer to be printed
;                       BC - number of bytes
;       Outputs         ________________________

PRINTHEX_BUFFER:

        ld d,8


_PRINTHEX_LOOP:
        ld a, (hl)
        call PRINT_HEX
        ld a, 020h
        call VDP_CHPUT
        inc hl
        dec bc
        ; decrement d and check if zero
        dec d
        ld a, d
        and a
        jr nz, _PRINTHEX_NEXT
        push hl
        ld hl, TXT_NEWLINE
        call VDP_PRINT
        ld d,8
        pop hl

_PRINTHEX_NEXT:
        ld a,b
        or c
        jp nz, _PRINTHEX_LOOP
        ret

; separate putch function that doesn't rely on a running MOS firmware
; UART0 initialization done by MOS firmware previously
; This utility doesn't run without MOS to load it anyway

VDP_CHPUT:
        push af
chput_uart0_available:
        in0 a, (UART0_LSR)
        and 01000000b ; 040h = Transmit holding register/FIFO and transmit shift register are empty
        jr z, chput_uart0_available
        pop af
        out0 (UART0_THR),a
        ; RST.LIL 10h
        RET
        

SER_CHPUT:
        push af
chput_uart1_available:
        in0 a, (UART1_LSR)
        and 01000000b ; 040h = Transmit holding register/FIFO and transmit shift register are empty
        jr z, chput_uart1_available
        pop af
        out0 (UART1_THR),a
        ; RST.LIL 10h
        RET

        
; Print a zero-terminated string in the UART1
;
SER_PRINT:	LD	A,(HL)
        OR	A
        RET	Z
        CALL    SER_CHPUT
        INC	HL
        JR	SER_PRINT
        
; Print a zero-terminated string in the VDP
;
VDP_PRINT:	LD	A,(HL)
        OR	A
        RET	Z
        CALL    VDP_CHPUT
        INC	HL
        JR	VDP_PRINT

TXT_NEWLINE:	DB     "\r\n", 0

