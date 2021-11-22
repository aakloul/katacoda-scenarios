

## Stack frame of the say function, right after the prolog

	STACK REPRESENTATION		Relative to ebp		memory allocated (bytes)

High memory
	| address of argument1	|	ebp+?			? bytes
	| RET: return address	|	ebp+?			? bytes			
	| caller-ebp		|  <--- ebp			? bytes
	|			|  <--- esp=ebp-?
Low memory


