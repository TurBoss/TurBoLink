#include "ez80f92.inc"

	ASSUME	ADL = 1

    ORG     0x40000

	CALL	_INIT

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

    STMIX				; Set mixed mode

	;CALL	EZ80_INIT
	
	; Disabled, handled by MOS v3 in FULL DUPLEX
	;CALL	UART0_INIT		; init UART 0 
	
	CALL	UART1_INIT		; init UART 1

	CALL	_SETMODE		; change VDP to terminal mode

	LD		HL, s_HELLORD
    CALL	VDP_PRINT
    
    
	LD		HL, s_AT
    CALL	SER_PRINT

    JP		_LOOP



_LOOP:


_SEND:

    CALL UART0_READ

	BIT 0, B
	JR Z, _RECV

    LD (s_TX_BUFF), A
    LD	HL, s_TX_BUFF

    CALL SER_PRINT

_RECV:

    CALL UART1_READ

    BIT 0, B
	JR Z, _DONE

    LD (s_RX_BUFF), A
    LD	HL, s_RX_BUFF

    CALL VDP_PRINT

_DONE:

    JP	_LOOP


_SETMODE:

	ASSUME ADL = 0					; set 16bit mode

	LD	A,	23
	RST.LIS	0x10

	LD	A,	0
	RST.LIS	0x10

	LD	A,	0xFF
	RST.LIS	0x10

	ASSUME ADL = 1					; set 24bit mode

	RET


#include	"ez80.inc"
#include	"uart.inc"
#include	"terminal.inc"
#include	"print.inc"


s_AT:	DB 	"ATI\r\n",	0
s_HELLORD:	DB 	"\r\nTurBo Link - Terminal client v1.0.1\r\n",	0
s_TX_BUFF:	DB	0,												0
s_RX_BUFF:	DB	0,												0


_END:	JP	_END

