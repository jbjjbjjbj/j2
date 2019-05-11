#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#define  MAX( a, b ) ( ( a > b) ? a : b ) 
#define  MIN( a, b ) ( ( a < b) ? a : b ) 

#define MEM_LEN 65536
#define PROG_BEGIN 65536/2
#define DEBUG 0

uint16_t handleChar( char c );

/* Mem stuff */
uint16_t mem[MEM_LEN];
void mem_put( uint16_t val );
uint16_t mem_get();

uint16_t *ip = mem;

/* Register stuff */
uint16_t regA, regB, regC;

void printReg() {
	printf("A: %d, B: %d, C: %d, IP: %d, i: %c\n", regA, regB, regC, *ip, mem[ *ip ]);
}

int main( void ) {
	char c;
	int i = PROG_BEGIN;
	*ip = PROG_BEGIN;

	while( ( c = getchar()) != EOF && i < MEM_LEN) {
		mem[i++] = c;
	}
	while( *ip ) { 
#if DEBUG == 1 
		printReg();
#endif
		*ip = handleChar( mem[ *ip ] );
	}

}

uint16_t handleChar( char c) {
	uint16_t temp = regA;

	switch( c ) {
		case '+':
			regA += regB;
			break;
		case '-':
			regA -= regB;
			break;
		case 'i':
			regA ++;
			break;
		case 'd':
			regA --;
			break;
		case '*':
			regA *= regB;
			break;
		case 'p':
			putchar(regA);
			break;
		case 'z':
			regA = regB;
			regB = temp;
			break;
		case 'c':
			regA = regC;
			regC = temp;
			break;
		case 's':
			mem_put( regA );
			break;
		case 'g':
			regA = mem_get();
			break;
		case 'j':
			if( regA == 0 ) {
				*ip = regC;
				regC = 0;
				return *ip;
			}
			break;
		case 'l':
			regA = mem[ ++(*ip) ];
		default:
			if( isdigit( c ) )
				regA = c - '0';
	}

	return *ip + 1;
}

void mem_put( uint16_t val ) {
	mem[regC] = val;
}

uint16_t mem_get() {
	return mem[ regC ];
}
