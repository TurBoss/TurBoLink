#include "ez80f92.inc"

	ASSUME	ADL = 1

    ORG     0x40000

	CALL	_INIT

	ALIGN	64			; The executable header is from byte 64 onwards

	DB		"MOS"		; Flag for MOS - to confirm this is LD valid MOS command
	DB		0x00		; MOS header version 0
	DB		0x01		; Flag for run mode (0: Z80, 1: ADL)


_INIT:

    ;STMIX				; Set mixed mode

	DI					; disable interrupts

    LD		SP,	0BFFFFh


	CALL	_MAIN

	RET


_MAIN:
	STMIX

	CALL	EZ80_INIT

	CALL	UART0_INIT
	CALL	UART1_INIT

	CALL	_SETMODE		; change VDP to terminal mode

	ASSUME ADL = 1



 	LD		HL, s_HELLORD
    CALL	SER_PRINT

	LD		HL, s_HELLORD
    CALL	VDP_PRINT

    JP		_LOOP


_LOOP:


_SEND:

    CALL UART0_READ

	BIT 0, B
	JR Z, _RECV

    LD (s_RESULT), A
    LD	HL, s_RESULT

    CALL SER_PRINT

_RECV:

    CALL UART1_READ

    BIT 0, B
	JR Z, _DONE

    LD (s_RESULT), A
    LD	HL, s_RESULT

    CALL VDP_PRINT

_DONE:

    JP _LOOP



; Write a stream of characters to the VDP
; HLU: Address of buffer containing data - if in 16-bit segment, U will be replaced by MB
;  BC: Number of characters to write out, or 0 if the data is delimited
;   A: End of data delimiter, i.e. 0 for C strings
;
;_SETMODE:
;		STMIX

;		LD		HL, h_CMODE        ; Address of text
;		LD		BC, 0              ; Set to 0, so length ignored...
;		LD		A, 0               ; Use character in A as delimiter

;		ASSUME ADL = 0

;		RST.LIS	0x18               ; This calls a RST in the eZ80 address space
;		RET

;



_SETMODE:

	ASSUME ADL = 0

	LD	A,	23
	RST.LIS	0x10

	LD	A,	0
	RST.LIS	0x10

	LD	A,	0xFF
	RST.LIS	0x10
	ASSUME ADL = 1

	RET


#include	"ez80.inc"
#include	"uart.inc"
#include	"terminal.inc"
#include	"print.inc"



h_CMODE:	DB 	23, 0, 0xFF, 0

s_HELLORD:	DB 	"\r\nTurBo Terminal client v1.0\r\n", 0
s_RESULT:	DB	0,	0

_END:	JP	_END

