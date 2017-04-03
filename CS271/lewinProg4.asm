TITLE Composites     (lewinProg4.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program #4     
; Due Date: 2/14/2016
; Description: This program calculates a given number of composite values.

INCLUDE Irvine32.inc

; Constants
	MIN			EQU		1		; mininum number of composites that can be displayed
	MAX			EQU		400		; maximum number of composites that can be displayed
	TEST_EVEN	EQU		2		; divisor used to test whether or not a dividend is even
	NUM_COLS	EQU		10		; number of composites to display on each line
	TRUE		EQU		1		; boolean constant
	FALSE		EQU		0		; boolean constant

.data
	header		BYTE	"Composite Numbers", 0dh, 0ah 
				BYTE	"Programed by Conrad Lewin", 0 
	exMsg		BYTE	"**EC: Check numbers against prime divisors", 0
	instrct		BYTE	"Enter the number of composite numbers you would like to see.", 0dh, 0ah
				BYTE	"I can print between 1 and 400 composites.", 0

	prompt1		BYTE	"Enter the number of composites to display [1 .. 400]: ", 0
	errMsg		BYTE	"Invalid input. Number is out of range.", 0

	curNum		DWORD	4
	isComp		DWORD	0
	primes		DWORD	2,3, 100 DUP(0)
	elemCnt		DWORD	2
	padding		BYTE	"   ", 0
	numComps	DWORD	0

	exitMsg		BYTE	"Results certified by Heron and other wonderful Greeks. Goodbye!", 0
.data?
	count		DWORD	?
	guess		SDWORD	?
	val			SDWORD	?
	
.code
main PROC
	call	printIntro
	call	getInput
	call	printComposites
	call	sayGoodbye
	call	Crlf
	exit	

main ENDP

Comment ?
Description: Prints a program header, a description of the extra credit attempted and the program instructions.
Recieves: n/a
Returns: n/a
Preconditions: n/a
Registers Changed: EDX
?

printIntro PROC

; print header
	mov		edx, OFFSET header
	call	WriteString
	call	Crlf
	call	Crlf

 ; print extra credit message
	mov		edx, OFFSET exMsg
	call	WriteString
	call	Crlf
	call	Crlf

; print program instructions
	mov		edx, OFFSET instrct
	call	WriteString
	call	Crlf
	call	Crlf
	ret

printIntro ENDP

Comment ?
Description: Gets valid integer input from the keyboard
Recieves: n/a
Returns: an unsigned integer value stored in global variable count
Preconditions: n/a
Registers Changes: EDX, EAX
?

getInput PROC

; print input prompt
	mov		edx, OFFSET prompt1
	call	WriteString

; read and save user input
	call	ReadDec
	mov		count, eax

; validate that input
	call	validateInput
	ret

getInput ENDP

Comment ?
Description: Validates the input read from the getInput procedure
Recieves: the value stored in global variable count
Returns: an unsigned integer value within the given range stored in global variable count
Preconditions: global variable count must contain an integer value
Registers Changes: EAX, EDX
?

validateInput PROC

; check for input outside the allowable vaue range
	mov		eax, count
	cmp		eax, MIN
	jb		InputError
	cmp		eax, MAX
	ja		InputError
	mov		count, eax
	jmp		ValidInput

; print and error message if the input is invalid and get new input from the user
InputError:
	mov		edx, OFFSET errMsg
	call	WriteString
	call	Crlf
	call	Crlf
	call	getInput

ValidInput:
	ret

validateInput ENDP

Comment ?
Description: Prints a user specified number of composites
Recieves: the values stored in global variables count and curNum
Returns: n/a
Preconditions: global variable count must contain an integer value
Registers Changes: ESI, EAX, EBX, ECX, EDX
?
printComposites PROC

; set counter for loop instruction
	mov		esi, 0
	mov		ecx, count

; determine whether or not the current number is composite or prime
GetComps:
	call	isComposite

; print the current number if composite, otherwise examine the next number
	cmp		isComp, TRUE
	je		PrintComp
	inc		curNum
	jmp		GetComps

; print the composite number
PrintComp:
	mov		eax, curNum
	call	WriteDec
	inc		numComps

; check the number of composites already printed. if 10 have been printed create a new row
	mov		eax, numComps
	mov		ebx, NUM_COLS
	cdq
	div		ebx
	cmp		edx, 0
	je		NewLine

; add padding between each composite
	mov		edx, OFFSET padding
	call	WriteString

; find the next composite unless the desired number of composites has already been found
Cont:
	inc		curNum
	loop	GetComps
	jmp		EndPrint

; create a new row
NewLine:
	call	Crlf
	jmp		Cont

EndPrint:
	ret

printComposites ENDP

Comment ?
Description: Tests a given integer value to determine whether it is prime or composite
Recieves: the value stored in the global variable curNum. This value starts at 4 and is incremented by the printComposites procedure
			whenever a composite is found.
Returns: a "boolean" valued stored in global variable isComp. if false is returned then the primes array is updated with a new prime factor, namely
			the current number being examined for compositeness
Preconditions: the default value of global variable curNum which is 4
Registers Changes: EAX, EBX, EDX, ESI
?

; test for an even number by dividing the current number by 2
isComposite PROC
	mov		ebx, TEST_EVEN
	mov		eax, curNum
	cdq
	div		ebx

; if the number is odd, then find its square root. otherwise, exit the procedure (all even numbers are composite)
	cmp		edx, 0
	jnz		GetRoot
	mov		isComp, TRUE
	jmp		EndComp

; find the root of an odd number. the root is returned in the global variable guess
GetRoot:
	call	sqrt

; compare the current prime number with the root of the current odd number. if the current prime is larger than the root of the current odd number
; then there is no need to check for further divisibility and we can conclude that the current odd number is prime. 
TestOdd:
	mov		ebx, guess
	cmp		primes[esi], ebx
	ja		NotFound

; otherwise, test the current number for divisibility with each prime factor in the primes array
	mov		eax, curNum
	cdq
	div		primes[esi]
	add		esi, TYPE primes

; if the current number is found to be divisible by one of the prime factors in the primes array, then a composite has been found
	cmp		edx, 0
	jnz		TestOdd
	mov		isComp, TRUE
	jmp		EndComp

; if the current number proves to be prime, then add that number to the next available spot in the primes array.
NotFound:
	mov		isComp, FALSE
	mov		eax, elemCnt
	mov		ebx, TYPE primes
	mul		ebx
	mov		ebx, curNum
	mov		primes[eax], ebx
	inc		elemCnt

; reset any pointer to a particular index in the primes array and return
EndComp:
	mov		esi, 0
	ret
isComposite ENDP

Comment ?
Description: Uses Heron's method to decipher the square root of a given number. Due to integer division, the exact square root is not calculated.
			x_{n+1}=(x_{n}+C/{x_{n}) / 2
Recieves: the value stored in global variable curNum
Returns: an integer square root stored in global variable guess
Preconditions: a positive number stored in curNum. This value must be greater than 3. Due to the use of integer division, an infinite loop occurs if the 
				the root of 3 is being calculated (not a problem if a floating point value is used). Since curNum will always be at least 4, there was no
				need to correct this.
Registers Changes: EAX, EBX
?

sqrt PROC

; divide the current number by two. This will serve as the initial square root quess
	mov		ebx, 2
	mov		eax, curNum
	cdq
	div		ebx
	mov		guess, eax

; refine the initial square root guess
GetRoot:
; save the current guess on the stack before dividing the current number by the current guess
	push	guess
	mov		ebx, guess
	mov		eax, curNum
	cdq
	div		ebx

; add the current guess to this quotient and then divide this sum by two
	add		eax, guess
	cdq
	mov		ebx, 2
	div		ebx

; save the new guess in the guess variable, restore the old guess and subtract the new guess from the old
	mov		guess, eax
	pop		ebx
	sub		eax, ebx

; get the absolute value of this difference. if the difference is 0 or 1, then the root has been found, otherwise, make another guess
	call	abs
	cmp		eax, 1
	jbe		RootFound
	jmp		GetRoot

; return the newest guess
RootFound:
	ret

sqrt ENDP

Comment ?
Description: Calculates the absolute value of a given number
Recieves: the value stored in the EAX register
Returns: a positive value stored in the EAX register
Preconditions: a valid integer value in the EAX register
Registers Changes: EAX, EDX
?

abs PROC
; check the sign of the value stored in EAX
	mov		val, eax
	js		NegNum
	jmp		PosNum

; if that number is negative then xor the bits and get the twos complement
NegNum:
	mov		edx, 0ffffffffh
	xor		eax, edx
	add		eax, 1 

; return the value in the EAX register	                              
PosNum:
	ret

abs ENDP

Comment ?
Description: Prints a goodbye message
Recieves: n/a
Returns: n/a
Preconditions: n/a
Registers Changes: EDX
?
; prints and exit message
sayGoodbye PROC
	call	Crlf
	call	Crlf
	mov		edx, OFFSET exitMsg
	call	WriteString
	call	Crlf
	ret
sayGoodbye ENDP

END main
