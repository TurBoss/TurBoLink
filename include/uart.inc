; UART0
PORTD_DRVAL_DEF       EQU    0ffh			;The default value for Port D data register (set for Mode 2).
PORTD_DDRVAL_DEF      EQU    0ffh			;The default value for Port D data direction register (set for Mode 2).
PORTD_ALT0VAL_DEF     EQU    0ffh			;The default value for Port D alternate register-0 (clear interrupts).
PORTD_ALT1VAL_DEF     EQU    000h			;The default value for Port D alternate register-1 (set for Mode 2).
PORTD_ALT2VAL_DEF     EQU    000h			;The default value for Port D alternate register-2 (set for Mode 2).

; UART1
PORTC_DRVAL_DEF       EQU    0ffh			;The default value for Port C data register (set for Mode 2).
PORTC_DDRVAL_DEF      EQU    0ffh			;The default value for Port C data direction register (set for Mode 2).
PORTC_ALT0VAL_DEF     EQU    0ffh			;The default value for Port C alternate register-0 (clear interrupts).
PORTC_ALT1VAL_DEF     EQU    000h			;The default value for Port C alternate register-1 (set for Mode 2).
PORTC_ALT2VAL_DEF     EQU    000h			;The default value for Port C alternate register-2 (set for Mode 2).

; baudrate divisors 1152000 UART 0
; 18432000 / (16*1152000) = 1,085069444444444
BRD_LOW_0                EQU    001h
BRD_HIGH_0               EQU    000h

; baudrate divisors 115200 UART 1
; 18432000 / (16*115200) = 10,85069444444444
BRD_LOW_1                EQU    00Ah
BRD_HIGH_1               EQU    000h

UART0_INIT:
    ; all pins to GPIO mode 2, high impedance input
    ld a, PORTD_DRVAL_DEF
    out0 (PD_DR),a
    ld a, PORTD_DDRVAL_DEF
    out0 (PD_DDR),a
    ld a, PORTD_ALT1VAL_DEF
    out0 (PD_ALT1),a
    ld a, PORTD_ALT2VAL_DEF
    out0 (PD_ALT2),a

    ; initialize for correct operation
    ; pin 0 and 1 to alternate function
    ; set pin 3 (CTS) to high-impedance input
    in0 a,(PD_DDR)
    or  00001011b; set pin 0,1,3
    out0 (PD_DDR), a
    in0 a,(PD_ALT1)
    and 11110100b; reset pin 0,1,3
    out0 (PD_ALT1), a
    in0 a,(PD_ALT2)
    and 11110111b; reset pin 3
    or  00000011b; set pin 0,1
    out0 (PD_ALT2), a
    
    in0 a,(UART0_LCTL)
    or 10000000b ; set UART_LCTL_DLAB
    out0 (UART0_LCTL),a
    ld a, BRD_LOW_0 ;// Load divisor low
    out0 (UART0_BRG_L),a
    ld a, BRD_HIGH_0 ;// Load divisor high
    out0 (UART0_BRG_H),a
    in0 a,(UART0_LCTL)
    and 01111111b ; reset UART_LCTL_DLAB
    out0 (UART0_LCTL),a
    ld a, 000h  ; reset modem control register
    out0 (UART0_MCTL),a
    ld a, 007h  ; enable and clear hardware fifo's
    out0 (UART0_FCTL),a
    ld a, 000h  ; no interrupts
    out0 (UART0_IER),a
    in0 a, (UART0_LCTL)
    or  00000011b    ; 8 databits, 1 stopbit
    and 11110111b    ; no parity
    out0 (UART0_LCTL),a

    RET

UART1_INIT:
	; all pins to GPIO mode 2, high impedance input
	ld a, PORTC_DRVAL_DEF
	out0 (PC_DR),a
	ld a, PORTC_DDRVAL_DEF
	out0 (PC_DDR),a
	ld a, PORTC_ALT1VAL_DEF
	out0 (PC_ALT1),a
	ld a, PORTC_ALT2VAL_DEF
	out0 (PC_ALT2),a

	; initialize for correct operation
	; pin 0 and 1 to alternate function
	; set pin 3 (CTS) to high-impedance input
	in0 a,(PC_DDR)
	or  00001011b; set pin 0,1,3
	out0 (PC_DDR), a
	in0 a,(PC_ALT1)
	and 11110100b; reset pin 0,1,3
	out0 (PC_ALT1), a
	in0 a,(PC_ALT2)
	and 11110111b; reset pin 3
	or  00000011b; set pin 0,1
	out0 (PC_ALT2), a

	in0 a,(UART1_LCTL)
	or 10000000b ; set UART_LCTL_DLAB
	out0 (UART1_LCTL),a
	ld a, BRD_LOW_1 ;// Load divisor low
	out0 (UART1_BRG_L),a
	ld a, BRD_HIGH_1 ;// Load divisor high
	out0 (UART1_BRG_H),a
	in0 a,(UART1_LCTL)
	and 01111111b ; reset UART_LCTL_DLAB
	out0 (UART1_LCTL),a
	ld a, 000h  ; reset modem control register
	out0 (UART1_MCTL),a
	ld a, 007h  ; enable and clear hardware fifo's
	out0 (UART1_FCTL),a
	ld a, 000h  ; no interrupts
	out0 (UART1_IER),a
	in0 a, (UART1_LCTL)
	or  00000011b    ; 8 databits, 1 stopbit
	and 11110111b    ; no parity
	out0 (UART1_LCTL),a

	RET
