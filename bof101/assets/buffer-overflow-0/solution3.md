

## Stack frame of the say function, right before the epilog

	STACK REPRESENTATION		Relative to ebp		memory allocated (bytes)

High memory
	| address of argument1	|	ebp+8			4 bytes
	| RET: return address	|	ebp+4			4 bytes
	| caller-ebp		|  <--- callee-ebp		4 bytes	
	| saved ebx 		|  				4 bytes	
	| buffer of size 2052	|				2052 bytes
	|			|  <--- esp+2056		4 bytes 		
Low Memory

The size of the offset is 2060 =  2052 (buffer size) + 4 (ebx size) + 4 (caller-ebp size) 
