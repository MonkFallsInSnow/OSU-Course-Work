TITLE Fibonacci     (fibonacci.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program 2             
; Due Date: 1/24/2015

; Description: This program gets an integer input by the user between 1 and 46 
; and calculates the Fibonacci numbers up to the given input value.

INCLUDE Irvine32.inc

; Constants
ENTER_KEY	= 13 ; ASCII value of the enter key
BUFFER_SIZE = 31 ; max number of characters allowed for the users name
LOWER_LIMIT = 1	 ; smallest number of Fibbonacci numbers that can be printed
UPPER_LIMIT = 46 ; largest number of Fibbonacci numbers that can be printed
NUM_COLS	= 5  ; number of output columns

; Function constants
newLine		TEXTEQU <call CrLf>
writeLine	TEXTEQU <call WriteString>

.data
progTitle	BYTE	"Fibonacci Numbers", 0
header		BYTE	"Programmed by ", 0
myName		BYTE	"Conrad Lewin", 0
promptName	BYTE	"What is your name? ", 0
greeting	BYTE	"Hello, ", 0	
userName	BYTE	30 DUP(0)
instruct	BYTE	"Enter the number of Fibonacci terms to be displayed. ", 0dh, 0ah
			BYTE	"Give the number as an integer in the range [1 .. 46]. ", 0
promptNum	BYTE	"How many Fibonacci terms do you want? ", 0
errorMsg	BYTE	"Invalid input. Enter an integer between 1 and 46.", 0
padding		BYTE	"     ", 0
n			DWORD	0
nMinus1		DWORD	0
goodBye		BYTE	"Results certified by Leonardo Pisano.", 0dh, 0ah
			BYTE	"Goodbye, ", 0

.data?
count		DWORD	? ; tracks the number of Fibonacci numbers being calculated

.code
main PROC

; display the program title and programmer’s name
	mov		edx, OFFSET progTitle
	writeLine
	newLine
	mov		edx, OFFSET header
	writeLine
	mov		edx, OFFSET myName
	writeLine
	newLine
	newLine

; get the user’s name, and greet the user
	mov		edx, OFFSET promptName
	writeLine
	mov		edx, OFFSET userName
	mov		ecx, BUFFER_SIZE
	call	ReadString
	newLine
	mov		edx, OFFSET greeting
	writeLine
	mov		edx, OFFSET userName
	writeLine
	newLine
	newLine

; prompt the user to enter the number of Fibonacci terms to be displayed. limit range to between 1 and 46
	mov		edx, OFFSET instruct
	writeLine
	newLine
	newLine

; get and validate the user input
GetNum:
	mov		edx, OFFSET promptNum
	writeLine
	call	ReadDec
	mov		count, eax
; print an error message if the user enters a number outside the specified range
	cmp		count, LOWER_LIMIT
	jb		Error1
	cmp		count, UPPER_LIMIT
	ja		Error1

; set up conditions for CalcFib loop
	mov		eax, n		; save n = 0 
	mov		ecx, count	; save the number of Fibonacci numbers to be displayed
	mov		count, 1	
	jmp		StartFib

; prints and error message if the user input is outside of the given range
Error1:
	newLine
	mov		edx, OFFSET errorMsg
	writeLine
	newLine
	newLine
	jmp		GetNum

; calculate and display all of the Fibonacci numbers up to and including the nth term.
; StartFib calculates the first Fibonacci number
StartFib:
	add		eax, 1				; eax is set to n = 0, 1 must be added to register to 
	mov		n, eax				; save this value to n
	call	WriteDec			; and print this value
	mov		edx, OFFSET padding ; prepare the column padding to be printed
	writeLine					; print the column padding
	cmp		ecx, 2				; determine whether the user input a number larger than 1
	jb		EndProgram			; if not, then stop calculating the Fibonacci numbers
	loop	CalcFib				; otherwise, continue calculating

; calculates the remaining Fibonacci numbers
CalcFib:
	inc		count				; update the number of Fibonacci numbers being calculated
	add		eax, nMinus1		; x sub n = x sub n-1 + x sub n-2
	call	WriteDec			
	mov		edx, OFFSET padding
	writeLine
; set up for the next iteration of the loop, redefines the numbers that will be added together to calculate the Fibonacci number
	mov		edx, n				
	mov 	nMinus1, edx
	mov		n, eax
; determine whether or not there are 5 numbers in the output row, adding a new line if 5 numbers are present
	mov		eax, count
	cdq
	mov		ebx, NUM_COLS
	div		ebx
	mov		eax, n
	cmp		edx, 0
	je		AddLine
; continue calculating or exit the loop if all numbers have been calculated
	loop	CalcFib
	jmp		EndProgram

; adds a new line if 5 numbers have been printed
AddLine:
	newLine
	loop	CalcFib
	
; display a parting message that includes the user’s name, and terminate the program
EndProgram:
	newLine
	mov		edx, OFFSET goodbye
	writeLine
	mov		edx, OFFSET userName
	writeLine
	newline
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
