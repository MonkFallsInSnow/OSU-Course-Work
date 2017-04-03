TITLE lewinProg6A     (lewinProg6A.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program 6A
; Due Date: 3/13/2016

; Description: Gets a digit string from the user then converts that string to an integer before calculating both its sum and average. 
; Also, converts an integer to a string in order to output it to the console

INCLUDE Irvine32.inc

MAX_NUM EQU 10	; max number of integers the user can enter
ZERO	EQU 48	; ascii value of the character digit '0'
NINE	EQU 58	; ascii value of the character digit '9'

Comment ?
Description: This macro prints a prompt for input and then reads that input
Recieves: prompt - offset of an array of chars
Returns: edx - the input string, eax - the number of bytes in the input string
Preconditions: n/a
Registers Changed: eax, edx
?

mGetString MACRO prompt:REQ, buffer:REQ
	push	ecx
	mov		edx, prompt
	call	WriteString
	mov		edx, OFFSET buffer
	mov		ecx, (SIZEOF buffer)-1
	call	ReadString
	pop		ecx

ENDM

Comment ?
Description: Displays a string to the console
Recieves: string - the offset of a character array
Returns: n/a
Preconditions: n/a
Registers Changed: none
?
mDisplayString MACRO string:REQ
	push	edx
	mov		edx, string
	call	WriteString
	pop		edx
ENDM

.data
	header		BYTE	"PROGRAMMING ASSIGNMENT 6: Designing low-level I/O procedures", 0dh, 0ah
				BYTE	"Written by: ", 0
	myName		BYTE	"Conrad Lewin", 0
	instrct		BYTE	"Please provide 10 unsigned decimal integers. Each number needs to be small", 0dh, 0ah
				BYTE	"enough to fit inside a 32 bit register. After you have finished inputting the", 0dh, 0ah
				BYTE	"raw numbers I will display a list of the integers, their sum, and their average value.", 0
	prompt1		BYTE	"Please enter an unsigned number: ", 0
	separator	BYTE	", ", 0
	dispMsg		BYTE	"You entered the following numbers:", 0
	sumMsg		BYTE	"The sum of these numbers is: ", 0
	avgMsg		BYTE	"The average is: ", 0
	goodbye		BYTE	"Is it time for spring break yet...? Thanks for playing!", 0
	errMsg	BYTE	"ERROR: You did not enter an unsigned number or your number was too big.", 0dh, 0ah

.data?
	numbers		DWORD	10 DUP(?)	; array of integers
	string		BYTE	101 DUP(?)	; array of characters
	buffer		DWORD	11 DUP(?)	; string buffer

.code
main PROC
	; print header
	mDisplayString OFFSET header
	mDisplayString OFFSET myName
	call	Crlf
	call	Crlf

	; print program instructions
	mDisplayString OFFSET instrct
	call	Crlf
	call	Crlf

	; read input and convert to numeric value
	push	OFFSET numbers
	push	OFFSET prompt1
	call	readVal
	call	Crlf

	; inform user of which numbers he/she entered
	mDisplayString OFFSET dispMsg
	call	Crlf

	; print digit string
	push	OFFSET separator
	push	OFFSET numbers
	push	OFFSET string
	call	writeVal
	call	Crlf
	call	Crlf

	; get/display sum
	push	OFFSET numbers
	call	getSum
	mDisplayString OFFSET sumMsg
	call	WriteDec
	call	Crlf

	; get/display average
	push	MAX_NUM
	push	eax
	call	getAvg
	mDisplayString OFFSET avgMsg
	call	WriteDec
	call	Crlf
	call	Crlf

	; display exit mesage
	mDisplayString OFFSET goodbye
	call	Crlf
	exit
main ENDP

Comment ?
Description: Reads a digit string and converts that string to its numeric equivalent
Recieves: prompt - offset of a char array (asks the user to enter a number), numbers - offset of 
			a integer array
Returns: edi - offset of an array of integers (numbers array)
Preconditions: n/a
Registers Changed: edi
?
readVal PROC USES ecx eax edx
	LOCAL strLen:DWORD

	PROMPT_PARAM = 8	; location in bytes of the prompt parameter on the stack frame
	ARRAY_PARAM	= 12	; location in bytes of the array parameter on the stack frame

	; save array address and set up loop counter
	mov		ecx, MAX_NUM
	mov		edi, [ebp+ARRAY_PARAM]
	push	edi

GetInput:
	; print prompt to get input and save the length of that string
	mGetString	[ebp+PROMPT_PARAM], buffer
	mov		strLen, eax

	; validate the input string (stored in edx)
	push	strLen
	push	edx	
	call	validate

	; test the integer flag returned by the validate procedure, getting new input if necessary
	cmp		eax, -1
	je		GetInput

	; save valid input into the numbers array
	mov		[edi], eax
	add		edi, TYPE esi
	loop	GetInput

	; return the address of the numbers array
	pop		edi
	ret		8
readVal	ENDP

Comment ?
Description: Validates user input after converting the digit string into a non-negative integer
Recieves: INPUT_PARAM - offset of a digit string (first parameter), STR_LEN_PARAM - length of the digit string (second parameter)
Returns: EAX - the integer equivalent to the given digit string
Preconditions: n/a
Registers Changed: EAX
?

validate PROC USES ecx esi ebx edx
	; isValid - flag indicating the validity of the converted string
	; intValue - the integer equivalent of the converted string
	; curVal - the current value of the constructed integer value
	LOCAL isValid:SDWORD, intValue:DWORD, curVal:DWORD

	INPUT_PARAM = 8		; location in bytes of the prompt parameter on the stack frame
	STR_LEN_PARAM = 12	; location in bytes of the prompt parameter on the stack frame
	MULTIPLIER = 10		; constant used as multiplier to calculate ...

	; initialize local variables
	mov		isValid, -1 ; sets an integer flag that will indicate whether the given input was valid or not
	mov		intValue, 0
	mov		curVal, 0

	; assign parameter values and clear the load direction flag
	mov		esi, [ebp+INPUT_PARAM]
	mov		ecx, [ebp+STR_LEN_PARAM]
	mov		ebx, 0
	cld

; convert and validate the digit string
GetChar:
	lodsb	; get each digit in the input string

	; make sure the current character is in the range of [48,58]
	cmp		al, ZERO
	jb		ErrorMsg
	cmp		al, NINE
	ja		ErrorMsg

	; convert the numeric character to an integer and save the value
	sub		al, ZERO
	movzx	ebx, al
	mov		intValue, ebx

	; construct the actual numeric value from each converted digit in the given string, making sure overflow does not occur
	mov		eax, curVal
	mov		ebx, MULTIPLIER
	mul		ebx
	jc		ErrorMsg
	add		eax, intValue
	mov		curVal, eax
	loop	GetChar

	; return the converted value
	mov		eax, curVal
	jmp		EndValidate

ErrorMsg:
	; print and error message and return the integer flag with a value of -1 (meaning the value was invalid)
	mDisplayString OFFSET errMsg
	mov		eax, isValid
		
EndValidate:
	ret		8
validate ENDP

Comment ?
Description: Converts an array of integer values to a digit string
Recieves: STR_ARRAY_PARAM - offset of an empty string array (frist parameter), NUM_ARRAY_PARAM - offset of an array of integers (second parameter), 
			; SEPARATOR_PARAM - offset of a character separator (third parameter)
Returns: a character array (global variable string)
Preconditions: n/a
Registers Changed: n/a
?
; remember to save registers
writeVal PROC
	DIVISOR = 10 ; constant used in converting an integer into a string
	
	; location of parameters on the stack frame
	STR_ARRAY_PARAM = 8
	NUM_ARRAY_PARAM = 12
	SEPARATOR_PARAM = 16

	;set up stack frame
	push	ebp
	mov		ebp, esp

	; save registers
	pushad

	; save parameters
	mov		edi, [ebp+STR_ARRAY_PARAM]
	mov		esi, [ebp+NUM_ARRAY_PARAM]

	; set up the loop counter and save the address of the given character array
	mov		ecx, MAX_NUM
	push	edi

GetNumber:
	; save the counter for the outer loop
	push	ecx

	; get the first number in the given integer array and set up the counter for the inner loop
	mov		eax, [esi]
	mov		ecx, 0

Convert:
	; get each digit in the number by dividing by 10 until a 0 remainder is produced
	cdq
	mov		ebx, DIVISOR
	div		ebx
	push	edx
	inc		ecx		; tracks how many times the current number was divided by 10 before producing a 0 remainder
	cmp		eax, 0
	jne		Convert
	
ToString:
	; examine each remainder and convert it to a character
	pop		eax
	add		al, ZERO
	stosb
	loop	ToString

	; print a separator after each completely converted number
	pop		ecx
	cmp		ecx, 1
	jne		PrintSeparator

Cont:
	; get the next number in the integer array
	add		esi, TYPE esi
	loop	GetNumber
	jmp		EndConvert

PrintSeparator:
	; add a separator to the character array
	mov		ebx, [ebp+SEPARATOR_PARAM]
	mov		eax,[ebx]
	stosb
	inc		ebx
	mov		eax,[ebx]
	stosb
	jmp		Cont

EndConvert:
	; get the starting address of the string array and display its contents
	pop		edi
	mDisplayString edi

	; restore all registers and clean up the stack frame
	popad
	pop		ebp
	ret		8
writeVal	ENDP

Comment ?
Description: Gets the sum of all integers in a given integer array
Recieves: ARRAY_PARAM - offset of an integer array (first parameter)
Returns: EAX - the sum of the numbers in the passed in array
Preconditions: an array of integers
Registers Changed: EAX
?
getSum PROC
	ARRAY_PARAM = 8

	; set up stack frame
	push	ebp
	mov		ebp, esp

	; save registers
	push	ecx
	push	esi

	; save the address of the integer array and set up the counter for the loop
	mov		esi, [ebp+ARRAY_PARAM]
	mov		eax, 0
	mov		ecx, MAX_NUM

Sum:
	; perform a summation on the integers in the array 
	add		eax, [esi]
	add		esi, TYPE esi
	loop	Sum

	; restore registers and clean up the stack frame
	pop		esi
	pop		ecx
	pop		ebp
	ret		4
getSum ENDP

Comment ?
Description: Gets the average of the sum returned by the getSum procedure
Recieves: TOTAL_PARAM - an integer value (first parameter), MAX_PARAM - total number of integers (second parameter)
Returns: EAX - the average of the given sum
Preconditions: a valid sum returned by the getSum procedure stored in the eax register
Registers Changed: EAX
?
getAvg PROC
	; location of the parameters on the stack frame
	TOTAL_PARAM = 8 
	MAX_PARAM = 12

	; set up stack frame
	push	ebp
	mov		ebp, esp

	; save registers
	push	ebx

	; get the average
	mov		ebx, [ebp+MAX_PARAM]
	mov		eax, [ebp+TOTAL_PARAM]
	cdq
	div		ebx

	; restore registers and clean up the stack frame
	pop		ebx
	pop		ebp
	ret		4
getAvg ENDP
END main