#include "ez80f92.inc"

	ASSUME	ADL = 1

    ORG     0x40000

	call	_INIT

	ALIGN	64			; The executable header is from byte 64 onwards

	DB		"MOS"		; Flag for MOS - to confirm this is LD valid MOS command
	DB		0x00		; MOS header version 0
	DB		0x01		; Flag for run mode (0: Z80, 1: ADL)


_INIT:
	DI					; disable interrupts

    LD		SP,	0BFFFFh

	CALL	_MAIN

	RET


_MAIN:

	CALL	EZ80_INIT

	CALL	UART0_INIT
	CALL	UART1_INIT


 	LD		HL, s_HELLORD
    CALL	SER_PRINT

	LD		HL, s_HELLORD
    CALL	VDP_PRINT


_LOOP:

;	ld	HL, s_HELLORD
;    call SER_PRINT

;	ld	HL, s_HELLORD
;    call VDP_PRINT

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


#include	"ez80.inc"
#include	"uart.inc"
#include	"terminal.inc"
#include	"print.inc"


s_CMODE:	DB 	"VDU 23 0 &FF", 0
s_HELLORD:	DB 	"\r\nTurBo Terminal client v1.0\r\n", 0
s_RESULT:	DB	0,	0

_END:	JP	_END

