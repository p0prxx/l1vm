/*
 * This file global.h is part of L1vm.
 *
 * (c) Copyright Stefan Pietzonke (jay-t@gmx.net), 2017
 * 
 * L1vm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * L1vm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with L1vm.  If not, see <http://www.gnu.org/licenses/>.
 */

//  global.h

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef unsigned char           U1;		/* UBYTE   */
typedef int16_t                 S2;     /* INT     */
typedef uint16_t                U2;     /* UINT    */
typedef int32_t                 S4;     /* LONGINT */

typedef long long               S8;     /* 64 bit long */
typedef double                  F8;     /* DOUBLE */


//#define DEBUG					1

#define M_ARM	0

/* set alignment for Android ARM */
#if M_ARM
#define ALIGN		__attribute__ ((aligned(8)))
#else
#define ALIGN
#endif

#define TRUE					1
#define FALSE					0


// machine
#define MAXREG				256			// registers (integer and double float)

#define MACHINE_BIG_ENDIAN      0       // endianess of host machine        

#define MAXLINELEN      512
#define MAXARGS         64
#define MAXBRACKETLEVEL	64
#define MAXEXPRESSION	32				// expressions per bracket level
#define MAXLINES		4096

#define REM_SB          "//"
#define ASM_SB 			"(ASM)"
#define ASM_END_SB		"(ASM_END)"

// data types UNKNOWN (0) -> x
#define UNKNOWN         7
#define BYTE            8
#define WORD            9
#define DOUBLEWORD      10
#define QUADWORD        11
#define DOUBLEFLOAT     12

#define STRING			13

// translate.h:
#define INTEGER			14
#define DOUBLE			15

#define MODULES                 32
#define MODULES_MAXFUNC         256



#define MAXCPUCORES		4		// threads that can be runned

#define RUNNING			1
#define STOP			0

// max input string len
#define MAXINPUT 512

// stacksize in bytes
#define STACKSIZE	64000

// jump call stack, for jsr, jsra
#define MAXSUBJUMPS		256

struct threaddata
{
	U1 *sp;			// stack pointer of mother thread
	U1 *sp_top;     // stack pointer top of mother thread
	U1 *sp_bottom;	// stack botttom of mother thread
	U1 *sp_thread;  // stack pointer of new thread
	U1 *sp_top_thread;
	U1 *sp_bottom_thread;
	S8 ep_startpos ALIGN;	// code startpos for new thread
	pthread_t id;			// thread ID
	U1 status;				// thread status
};

struct t_var
{
    U1 type;
    U1 digitstr[MAXLINELEN];
    U1 digitstr_type;
	U1 base;
};

#define MAXDATAINFO             1024 // data names

struct data_info
{
    U1 name[MAXLINELEN];
    S8 offset;
    S8 size;
    S8 end;
	S8 type_size;
	U1 type;
	
	// compiler
	U1 value_str[MAXLINELEN];
	U1 type_str[2];
};

#define MAXOPCODES              60

struct opcode
{
    U1 op[16];
    S2 args;
    U1 type[4];
};


// compiler:
struct translate
{
	U1 op[32];
	S2 args;
	U1 type[4];
	U1 assemb_op;
};

#define MAXLABELS				1024
#define LABELLEN				64

struct label
{
	U1 name[LABELLEN];
	S8 pos;
};


// shell arguments
#define MAXSHELLARGS			32
#define MAXSHELLARGLEN			256

struct opcode opcode[MAXOPCODES];

// 60 opcodes
#define PUSHB   0
#define PUSHW   1
#define PUSHDW  2
#define PUSHQW  3
#define PUSHD   4

#define PULLB   5
#define PULLW   6
#define PULLDW  7
#define PULLQW  8
#define PULLD   9

#define ADDI    10
#define SUBI    11
#define MULI    12
#define DIVI    13

#define ADDD    14
#define SUBD    15
#define MULD    16
#define DIVD    17

#define SMULI   18
#define SDIVI   19

#define ANDI    20
#define ORI     21
#define BANDI   22
#define BORI    23
#define BXORI   24
#define MODI    25

#define EQI     26
#define NEQI    27
#define GRI     28
#define LSI     29
#define GREQI   30
#define LSEQI   31

#define EQD     32
#define NEQD    33
#define GRD     34
#define LSD     35
#define GREQD   36
#define LSEQD   37

#define JMP     38
#define JMPI    39

#define STPUSHB     40
#define STPOPB      41

#define STPUSHI   42
#define STPOPI   43

#define STPUSHD   44
#define STPOPD    45

#define LOADA     46
#define LOADD     47

#define INTR0      48
#define INTR1      49

// superopcodes for counter loops
#define INCLSIJMPI 50
#define DECGRIJMPI 51

#define MOVI	52
#define MOVD	53

#define LOADL   54
#define JMPA	55

#define JSR		56
#define JSRA	57
#define RTS		58

#define LOAD    59