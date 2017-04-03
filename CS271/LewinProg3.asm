TITLE LewinProg3     (LewinProg3.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program 3     
; Due Date: 2/7/2016

; Description: This program gets a number of negative integer values between -100 and -1
; from the user, ensures this data is valid and then calculates their sum and average.

INCLUDE Irvine32.inc

LOWER_LIMIT		EQU		-100

.data

; GreetUser variables
	intro		BYTE	"Welcome to the Integer Accumulator by ", 0
	myName		BYTE	"Conrad Lewin", 0
	extraCredit	BYTE	"**EC: Number the lines during user input.", 0
	prompt1		BYTE	"What is your name? ", 0
	userName	BYTE	30 DUP(0)
	greeting	BYTE	"Hello, ", 0
	fullStop	BYTE	".", 0

; GetNumber variables
	prompt2		BYTE	"Please enter numbers in [-100, -1].", 0dh, 0ah
				BYTE	"Enter a non-negative number when you are finished to see the results.", 0dh, 0ah, 0
	prompt3		BYTE	") Enter number: ", 0
	info1		BYTE	"You entered ", 0
	info2		BYTE	" valid numbers.", 0		
	errorMsg	BYTE	"Invalid input. Please enter a number between -100 and -1.", 0
	count		DWORD	0
	specialMsg	BYTE	"Zero valid numbers?! I guess you aren't interested in experiencing", 0dh, 0ah 
				BYTE	"my glorious computing power...", 0

; GetSum and GetAvg variables
	sumDisplay	BYTE	"The sum of your valid numbers is ", 0
	avgDisplay	BYTE	"The rounded average is ", 0

; SayGoodbye variables
	goodBye		BYTE	"Thank you for playing Integer Accumulator!", 0dh, 0ah
				BYTE	"It's been a pleasure to meet you, ", 0

.data?
	num			SDWORD	?		; tracks the current input value
	sum			SDWORD	?		; tracks the current sum of all given input values
	avg			SDWORD	?		; stores the average of all given input values

.code
main PROC
	
; greet the user
	call	GreetUser
	call	Crlf
	call	Crlf

; get the numbers input by the user and calculate there sum
	call	GetNumber
	call	Crlf
	call	Crlf
	cmp		count, 0
	jz		EndProgram

; calculate the average of the input values
	call	GetAvg

; display the sum and averages of the input values
	call	PrintInfo
	call	Crlf
	call	Crlf

; display a parting message and exit the program
EndProgram:
	call	SayGoodbye
	call	Crlf
	call	Crlf

	exit

main ENDP

; Procedures

; GreetUser introduces the program and its creator, gets the users name and displays a greeting
GreetUser PROC USES edx

; introduce program
	mov		edx, OFFSET intro
	call	WriteString
	mov		edx, OFFSET myName
	call	WriteString
	call	Crlf
	mov		edx, OFFSET extraCredit
	call	WriteString
	call	Crlf
	call	Crlf

; get user name
	mov		edx, OFFSET prompt1
	call	WriteString
	call	GetName

; display greeting
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	mov		edx, OFFSET fullStop
	call	WriteString
	ret

GreetUser ENDP


; GetName reads input from the keyboard, saving that input as the user's name
GetName PROC USES ecx edx

	mov		edx, OFFSET userName		; setup buffer
	mov		ecx, SIZEOF userName + 1	; set max characters to read from keyboard
	call	ReadString
	ret		

GetName ENDP


; GetNumber gets a user input value, making sure it is within the given range. As valid numbers are input, the sum
; of these numbers is calcuated
GetNumber PROC USES edx eax

; instruct user to enter a number in a given range
	mov		edx, OFFSET prompt2
	call	WriteString
	call	Crlf

; prompt use to enter a number
Input:
	mov		eax, count
	add		eax, 1
	call	WriteDec
	mov		edx, OFFSET prompt3
	call	WriteString
	call	ReadInt

; validate the input
	pushfd							; save status flags
	mov		num, eax
	jo		Error					; print error message if the input causes overflow
	cmp		num, LOWER_LIMIT		
	jl		Error					; print error message if the input is smaller than -100	
	popfd							; restore old status flags to test the sign flag					
	jns		NumCount				; end user input cycle if that input is positive
	inc		count					; track the number of integers input
	call	GetSum					; get the current sum of the input values
	jmp		Input					; continue loop

; prints an error message when invalid input is detected and then jumps back into the input loop
Error:
	mov		edx, OFFSET errorMsg
	call	WriteString
	call	Crlf
	popfd							; restore stack
	jmp		Input

; prints how many valid numbers were entered
NumCount:
	mov		edx, OFFSET info1
	call	WriteString
	mov		eax, count
	call	WriteDec
	mov		edx, OFFSET info2
	call	WriteString
	cmp		count, 0
	jnz		EndMethod
	call	Crlf
	call	Crlf
	mov		edx, OFFSET specialMsg
	call	WriteString

EndMethod:
	ret

GetNumber ENDP


; GetSum adds the latest input value to the previous one (first calculation is eax = sum + num, where sum = 0)
GetSum PROC USES eax

	mov		eax, num
	add		eax, sum
	mov		sum, eax
	ret

GetSum ENDP


; GetAvg calculates the average of all the input values
GetAvg PROC USES eax

	mov		eax, sum
	cdq
	idiv	count
	mov		avg, eax
	ret

GetAvg ENDP


; PrintInfo displays the sum and average of the given input values
PrintInfo PROC USES edx eax

; display the sum
	mov		edx, OFFSET sumDisplay
	call	WriteString
	mov		eax, sum
	call	WriteInt
	call	Crlf

; display the average
	mov		edx, OFFSET avgDisplay
	call	WriteString
	mov		eax, avg
	call	WriteInt
	ret

PrintInfo ENDP

; SayGoodbye prints a parting message
SayGoodbye PROC USES edx

	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	mov		edx, OFFSET fullStop
	call	WriteString
	ret

SayGoodbye ENDP

END main
