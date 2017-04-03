TITLE lewinProg5     (lewinProg5.asm)

; Author: Conrad Lewin
; Email: lewinc@oregonstate.edu
; Course: CS 271-400
; Project ID: Program 5          
; Due Date: 2/28/2016
; Description: This program generates a user specified number of random integers and then stores them in an array. The array 
; is then sorted and the median value is calculated.

INCLUDE Irvine32.inc

MIN = 10			; minimum number of random numbers to be generated
MAX = 200			; maximum number of random numbers to be generated
LO = 100			; smallest random number that can be generated
HI = 999			; largest random number that can be generated
ARRAY_SIZE  = 200	; size of the array that will store the random numbers
TEST_EVEN = 2		; number used to test for an even number
COL_NUM = 10		; number of output columns
REQUEST_PARAM = 8	; location of numbers to generate on the stack frame
ARRAY_PARAM = 12	; location of the array on the stack frame
TITLE_PARAM = 16	; location of an array description on the stack frame

.data
	header		BYTE	"Sorting Random Integers", 0
	author		BYTE	"Programmed by Conrad Lewin", 0
	instruct	BYTE	"This program generates random numbers in the range [100 .. 999], displays the", 0dh, 0ah
				BYTE	"original list, sorts the list, and calculates the median value. Finally, it", 0dh, 0ah
				BYTE	"displays the list sorted in descending order.", 0
	exitMsg		BYTE	"Results certified by folks smarter than me.", 0
	prompt1		BYTE	"How many numbers should be generated? [10 .. 200]: ",0
	errMsg		BYTE	"Invalid input.", 0
	unsorted	BYTE	"The unsorted random numbers:", 0
	sorted		BYTE	"The sorted list:", 0
	dispMedian	BYTE	"The median is ", 0
	padding		BYTE	"   ", 0

.data?
	array		DWORD	ARRAY_SIZE DUP(0)
	request		DWORD	?

.code
main PROC
	call	Randomize ; generates seed for random number generation
	
	; print program introduction
	call	printIntro

	; get number of random numbers to generate
	push	OFFSET request
	call	getData

	; populate the array
	push	OFFSET array
	push	request
	call	fillArray
	call	Crlf

	; print the unsorted array contents
	push	OFFSET unsorted
	push	OFFSET array
	push	request
	call	printArray
	call	Crlf
	call	Crlf

	; sort the array
	push	OFFSET array
	push	request
	call	sortArray

	; calculate and display the median
	mov		edx, OFFSET dispMedian
	call	WriteString
	push	OFFSET array
	push	request
	call	getMedian
	call	WriteDec
	call	Crlf
	call	Crlf

	; print the sorted array
	push	OFFSET sorted
	push	OFFSET array
	push	request
	call	printArray
	call	Crlf
	call	Crlf

	; print an exit message
	call	goodbye
	exit	
main ENDP

Comment ?
Description: Prints a program header and instructions.
Recieves: n/a
Returns: n/a
Preconditions: n/a
Registers Changed: none (registers used are save and restored)
?
printIntro PROC USES EDX
	; print program header
	mov		edx, OFFSET header
	call	WriteString
	call	Crlf

	;print program author
	mov		edx, OFFSET author
	call	WriteString
	call	Crlf
	call	Crlf

	; print program instructions
	mov		edx, OFFSET instruct
	call	WriteString
	call	Crlf
	call	Crlf
	ret
printIntro ENDP

Comment ?
Description: Gets the number of random numbers to generate from the user
Recieves: reference to a DWORD variable that stores the number of numbers to generate (request)
Returns: a valid value in the request variable
Preconditions: n/a
Registers Changed: none (registers used are save and restored)
?
getData PROC
	; create stack frame
	push	ebp
	mov		ebp, esp

	pushad ; save registers

Input:
	; display prompt and get input
	mov		edx, OFFSET prompt1
	call	WriteString
	call	ReadDec

	; validate input
	cmp		eax, MIN
	jb		Invalid
	cmp		eax, Max
	ja		Invalid
	jmp		HaveData

Invalid:
	; print an error message if input is outside the given range
	mov		edx, OFFSET errMsg
	call	WriteString
	call	Crlf
	jmp		Input

HaveData:
	; once valid input is recieved...
	mov		ebx, [ebp+REQUEST_PARAM] ; get the address of the request variable 
	mov		[ebx], eax				 ; save the user input in that variable

	popad ; restore registers

	; clean up stack frame
	pop		ebp
	ret		4
getData ENDP

Comment ?
Description: Fills the arrray with random numbers
Recieves: reference to an array variable and the number of random numbers to be generated (request passed by value)
Returns: an array filled with a given number (request value) of random integer elements
Preconditions: n/a
Registers Changed:  none (registers used are save and restored)
?
fillArray PROC
	; set up stack frame
	push	ebp
	mov		ebp, esp

	pushad ; save registers

	; save the address of the array and the number of elements to generate
	mov		ecx, [ebp+REQUEST_PARAM]
	mov		edi, [ebp+ARRAY_PARAM]

Fill:
; this section of code is based on slide 7 in lecture 20
	; generate a random number
	mov		eax, HI
	sub		eax, LO
	inc		eax		
	call	RandomRange
	add		eax, LO
 ; -------------------------------------

	; add that number to the array at the next available index
	mov		[edi], eax
	add		edi, TYPE array
	loop	Fill

	popad	; restore registers

	; clean up stack frame
	pop		ebp
	ret		8
fillArray ENDP

Comment ?
Description: Sorts an array of integers using selection sort
Recieves: reference to an array variable and the number of random numbers to be generated (request passed by value)
Returns: an array sorted in ascending order (array passed by reference)
Preconditions: an array with at least one element
Registers Changed: none (registers used are save and restored)
?
sortArray PROC USES eax esi ecx ebx edx
	LOCAL	curNum:DWORD, count:DWORD, minIndex:DWORD, originalMin:DWORD

	; save the address of the array and the number of elements to loop through
	mov		esi, [ebp+ARRAY_PARAM]
	mov		ecx, [ebp+REQUEST_PARAM]
	sub		ecx, 1

	; initialize local variables
	mov		count, ecx 
	mov		originalMin, 0 ; tracks index of the orginal minimum
	mov		minIndex, 0	; tracks index of the current mininimum
	mov		eax, 0 ; tracks current index

OuterLoop:
	; save counter for the outer loop and address of the currently examined element in the array on the stack
	push	ecx
	push	esi

	; save the current element to a local variable and set the counter for the inner loop
	mov		ebx, [esi]
	mov		curNum, ebx
	mov		ecx, count

InnerLoop:
	; track the current index
	add		eax, TYPE array 
	add		esi, TYPE array 

	; compare the current index to the current minimum
	mov		ebx, [esi]
	cmp		curNum, ebx
	ja		ChangeMin
	loop	InnerLoop

	; check to see if a new minimum value was found
	mov		edx, minIndex
	cmp		edx, originalMin
	je		Cont

SwapIndex:
	; if the minimum value was updated during the loop, then swap the current minimum with the intial minimum
	push	[ebp+ARRAY_PARAM]
	push	minIndex
	push	originalMin
	call	swap

Cont:
	; setup conditions for outer loop and get a new intial minimum
	pop		esi
	pop		ecx
	sub		count, 1
	add		esi, TYPE array 
	add		originalMin, TYPE array
	mov		eax, originalMin
	mov		minIndex, eax
	loop	OuterLoop
	jmp		EndSort

ChangeMin:
	; if the current element is smaller than the current min, then update the current minimum and save that value's index
	mov		curNum, ebx
	mov		ebx, [esi]
	mov		minIndex, eax
	loop	InnerLoop
	jmp		SwapIndex

EndSort:
	ret		8
sortArray ENDP

Comment ?
Description: Swaps to elements in an array
Recieves: a reference to an array, two variables containing the index of the elements to swap
Returns: the passed array with the values at the given indicies swapped
Preconditions: an array with at least one element
Registers Changed: none (registers used are save and restored)
?
swap PROC USES eax ebx edi edx
	LOCAL	temp:DWORD

	; save passed in arguments
	mov		eax, [ebp+8] ; contains original min index
	mov		ebx, [ebp+12] ; contains new min index
	mov		edi, [ebp+16] ; pointer to array
	mov		edx, [edi+ebx] ; temp for new min val

	; swap elements and update the array
	mov		temp, edx
	mov		edx, [edi+eax]
	mov		DWORD PTR [edi+ebx], edx
	mov		edx, temp
	mov		DWORD PTR [edi+eax], edx

	ret		12
swap ENDP

Comment ?
Description: Calculates and displays the median value in a given array
Recieves: a reference to an array of integers and the number elements in that array
Returns: the median value in the given array in register EAX
Preconditions: an array with at least one element
Registers Changed: EAX
?
getMedian PROC 
	; set up stack frame
	push	ebp
	mov		ebp, esp

	; save registers
	push	ecx
	push	ebx
	push	esi
	push	edx

	; determine the parity of the number of elements in the array
	mov		ecx, TYPE array 
	mov		ebx, TEST_EVEN
	mov		esi, [ebp+ARRAY_PARAM]
	mov		eax, [ebp+REQUEST_PARAM]
	cdq
	div		ebx
	cmp		edx, 0
	je		CalcMedian

	; if odd parity, then save the middle element
	mul		ecx
	mov		eax, [esi+eax]
	jmp		HaveMedian

CalcMedian:
	; if even parity, then get the average of the two elements that make up the middle of the array
	mul		ecx
	mov		edx, [esi+eax]
	sub		eax, TYPE array 
	mov		ecx, [esi+eax]
	add		edx, ecx
	mov		eax, edx
	cdq
	div		ebx	

HaveMedian:
	;restore registers
	pop		edx
	pop		esi
	pop		ebx
	pop		ecx

	; clean up stack frame
	pop		ebp
	ret		8
getMedian ENDP

Comment ?
Description: Prints all elements in a given array
Recieves: a reference to an array of integers, a reference to an array of characters that describes the array of integers,
			the number of elements in the array of integers
Returns: n/a
Preconditions: n/a
Registers Changed: none
?
printArray PROC USES ecx esi edx eax ebx
	LOCAL	count:DWORD ; number of elements currently displayed

	; save arguments and print the array descriptor
	mov		count, 0
	mov		ecx, [ebp+REQUEST_PARAM]
	mov		esi, [ebp+ARRAY_PARAM]
	mov		edx, [ebp+TITLE_PARAM]
	call	WriteString
	call	Crlf

Print:
	; loop through the array, printing the value at the current index
	mov		eax, [esi]
	call	WriteDec
	mov		edx, OFFSET padding
	call	WriteString
	add		esi, TYPE array 

	; check the current number of elements displayed and make a new row when the all columns in the current row have been filled
	inc		count
	mov		eax, count
	mov		ebx, COL_NUM
	cdq
	div		ebx
	cmp		edx, 0
	je		Newline
	loop	Print
	jmp		EndPrint

Newline:
	; create a new row
	call	Crlf
	loop	Print

EndPrint:
	ret		12
printArray ENDP

Comment ?
Description: Prints a exit message
Recieves: a reference to an array of characters that spells out a n exit message
Returns: n/a
Preconditions: n/a
Registers Changed: none
?
goodbye PROC USES edx
	; print exit message
	mov		edx, OFFSET exitMsg
	call	WriteString
	call	Crlf
	ret
goodbye ENDP

END main
