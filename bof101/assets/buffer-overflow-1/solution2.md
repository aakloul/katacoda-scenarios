

## Stack frame of the say function, after the local buffer has been allocated in the stack

	STACK REPRESENTATION		Relative to ebp		memory allocated

High memory
	| address of argument1	|	ebp+8			4 bytes
	| RET: return address	|	ebp+4			4 bytes
	| caller-ebp		|  <--- callee-ebp		4 bytes
	| content of  ebx	|  	ebp-4			? bytes
	| buffer (local) 	|	ebp-?			? bytes
	|			|  <--- esp=ebp-?
Low memory

