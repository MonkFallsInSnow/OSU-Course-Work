TITLE Project01     (project01.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program 1              
; Due Date: 1/17/2015

; Description: This program takes two numbers input by the user and calculates their sum, difference, product, quotient and remainder
; until the user decides to exit the program.

INCLUDE Irvine32.inc

newLine		TEXTEQU		<call CrLf>		; directive that calls the CrLf procedure
writeLine	TEXTEQU		<call WriteString>	; directive that calls the WriteString procedure
printSign	TEXTEQU		<call WriteChar>	; prints a basic arithmetic sign, also used to print a space between operand and operator
printNum	TEXTEQU		<call WriteDec>		; prints an operand

; ASCII constant values for operators
ADD_SIGN	EQU		43
MINUS_SIGN	EQU		45
DIV_SIGN	EQU		246
MUL_SIGN	EQU		42
EQUAL_SIGN	EQU		61

SPACE		EQU		32		; ASCII constant value for space character
YES		EQU		121		; ASCII constant value for lowercase y character

.data
myName		BYTE	"Conrad Lewin", 0
progTitle	BYTE	"Elementary Arithmetic by ", 0
instruct	BYTE	"Enter 2 numbers, and I'll show you the sum, difference, product,", 0ah, 0dh
			BYTE	"quotient, and remainder.", 0
prompt1		BYTE	"Enter first number: ", 0
prompt2		BYTE	"Enter second number: ", 0
endMessage	BYTE	"That's all folks!", 0
errorString	BYTE	"Invalid input. The second number must be less than the first!", 0
remain		BYTE	"Remainder ", 0
prompt3		BYTE	"Would you like to try again (y/n)? ", 0
buffer		BYTE	1 DUP(0)
extraCredit	BYTE	"**EC: Program verifies second number is less than the first.", 0ah, 0dh
			BYTE	"**EC: Program repeats until the user chooses to quit.", 0

.data?
num1		DWORD	?
num2		DWORD	?
sum		DWORD	?
diff		DWORD	?
product		DWORD	?
quotient	DWORD	?
remainder	DWORD	?

.code
main PROC

; output name and program title to screen
	mov		edx, OFFSET progTitle
	writeLine
	mov		edx, OFFSET myName
	writeLine
	newline
	mov		edx, OFFSET extraCredit
	writeLine
	newLine
	newline

; output user instructions
	mov		edx, OFFSET instruct
	writeLine
	newline
	newline

; prompt user to enter two numbers
GetInput:
	mov		edx, OFFSET prompt1
	writeLine
	call		ReadDec
	mov		num1, eax
	mov		edx, OFFSET prompt2
	writeLine
	call		ReadDec
	mov		num2, eax

; check for valid input, i.e num1 > num2
	cmp		eax, num1		
	jg		ErrorMsg		
	jmp		Calculate		

; print an error message and reprompt the user for input
ErrorMsg:					
	mov		edx, OFFSET errorString
	writeLine
	newLine
	newLine
	jmp		GetInput

	
; calculate and output sum
Calculate:
	newLine
	mov		eax, num1
	add		eax, num2
	mov		sum, eax
	mov		eax, num1
	printNum
	mov		al, SPACE
	printSign
	mov		al, ADD_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, num2
	printNum
	mov		al, SPACE
	printSign
	mov		al, EQUAL_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, sum
	printNum
	newline

	
; calculate and output diference
	mov		eax, num1
	sub		eax, num2
	mov		diff, eax
	mov		eax, num1
	printNum
	mov		al, SPACE
	printSign
	mov		al, MINUS_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, num2
	printNum
	mov		al, SPACE
	printSign
	mov		al, EQUAL_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, diff
	printNum
	newline

; calculate and output product
	mov		eax, num1
	mul		num2
	mov		product, eax
	mov		eax, num1
	printNum
	mov		al, SPACE
	printSign
	mov		al, MUL_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, num2
	printNum
	mov		al, SPACE
	printSign
	mov		al, EQUAL_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, product
	printNum
	newline

	
; calculate and output quotient and reminder
	mov		eax, num1
	cdq
	div		num2
	mov		quotient, eax
	mov		remainder, edx
	mov		eax, num1
	printNum
	mov		al, SPACE
	printSign
	mov		al, DIV_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, num2
	printNum
	mov		al, SPACE
	printSign
	mov		al, EQUAL_SIGN
	printSign
	mov		al, SPACE
	printSign
	mov		eax, quotient
	printNum
	mov		al, SPACE
	printSign
	mov		edx, OFFSET remain
	writeLine
	mov		eax, remainder
	printNum
	newline
	newline

; ask the user if they would like to run the program again
	mov		edx, OFFSET prompt3
	writeLine
	newline
	call		ReadChar
	cmp		al, YES

; start the program over
	je		GetInput

; display a terminating message
	newline
	mov		edx, OFFSET endMessage
	call		WriteString
	newline
	
	exit	; exit to operating system
main ENDP

END main
