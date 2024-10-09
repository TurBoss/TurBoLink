
UART0_READ:
    ; Check if the receive buffer is full
    IN0 B, (UART0_LSR)
    BIT 0, B

    RET Z  ; Return immediately if no character is available

    ; Read the character from the receive buffer
    IN0 A, (UART0_RBR)

    RET

UART1_READ:
	; Check if the receive buffer is full
	IN0 B, (UART1_LSR)
	BIT 0, B

	RET Z  ; Return immediately if no character is available

	; Read the character from the receive buffer
	IN0 A, (UART1_RBR)

	RET
