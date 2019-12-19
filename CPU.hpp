#include <bitset>
#include <stdint.h>
#include <iomanip>
#include <iostream>

#define STACK_SIZE 0x100

/*
Class for 6502 CPU Implementaiton
*/


/*
Emulates the interface signal pins found on the 6502
vss1,2
rdy
clock1,2,3
irq, nmi, sync, vcc
rw, nc1-3
*/
union Interface_Signals
{
	struct interface_pins
	{
		uint16_t 
			vss1 : 1, rdy : 1, clock1_out : 1, irq : 1, 
			nc1 : 1, nmi : 1, sync : 1, vcc : 1, 
			res : 1, : 1, set_overflow : 1, clock0_in : 1,
			nc2 : 1, nc3 : 1, rw : 1, vss2 : 1;
	} i_pins_bits;
	uint16_t i_pins;
};




/*
Emulates d0-d7 pins on the 6502 CPU
*/
union Data_Pins{
	struct data_out_pin
	{
		uint8_t 
			d0 : 1, d1 : 1, d2 : 1, d3 : 1,
			d4 : 1, d5 : 1, d6 : 1, d7 : 1;
	} data_pins_bits;

	uint8_t data_pins;
};


/*
Emulates a0-a15 pins on the 6502 CPU
*/
union Address_Pins
{
	struct address_out_pin
	{
		uint16_t 
			a0 : 1, a1 : 1, a2 : 1, a3 : 1, 
			a4 : 1, a5 : 1, a6 : 1, a7 : 1,
			a8 : 1, a9 : 1, a10 : 1, a11 : 1,
			a12 : 1, a13 : 1, a14 : 1, a15 : 1;
	} address_pins_bits;
	uint16_t address_pins;
};


/*
Emulates bits 0-7 in a general purpose 8-bit register on the 6502
*/
union Reg_6502
{
	struct reg_6502_bit
	{
		uint8_t
			b0 : 1, b1 : 1, b2 : 1, b3 : 1,
			b4 : 1, b5 : 1, b6 : 1, b7 : 1;
	} gen_reg_bits;
	uint8_t gen_reg;
};


/*
Emulates bits 0-15 in the 16-bit PC register on the 6502
*/
union PCReg_6502
{
	struct pc_reg_6502_bit
	{
		uint8_t
			b0 : 1, b1 : 1, b2 : 1, b3 : 1,
			b4 : 1, b5 : 1, b6 : 1, b7 : 1,
			b8 : 1, b9 : 1, b10 : 1, b11 : 1,
			b12 : 1, b13 : 1, b14 : 1, b15 : 1;
	} pc_reg_bits;
	uint16_t pc_reg;
};


/*
Emulates bits 0-7 in a general purpose 8-bit register on the 6502 (similar to Reg_6502, but useful names)
*/
union StatusReg_6502
{
	struct status_reg_6502_bit
	{
		uint8_t 
			carry : 1, zero : 1, irq_disable : 1, decimal_mode : 1,
			brk_command : 1, unused : 1, overflow : 1, negative : 1;
	};
	uint8_t status_reg;
};


/*
Emulates the 6502 256-bit stack
*/
struct Stack_6502
{
	uint8_t data[STACK_SIZE];	//256 bytes of stack available
};



struct CPU
{
	//pins
	Interface_Signals interfacePins;
	Data_Pins dataPins;
	Address_Pins addressPins;

	//stack
	Stack_6502 stack;

	//registers
	Reg_6502 accumulator;
	Reg_6502 x_reg;
	Reg_6502 y_reg;
	Reg_6502 stack_pointer;
	PCReg_6502 program_counter;
	StatusReg_6502 status_reg;

	//instructions
	void reset();
	void clock();


	/*
	Prints all registers to the screen
	*/
	void printState() const;
	
	/*
	Prints the stack to the console
	Usage:
		If you want a table view of the stack, set elemnts to -1 and give the rows cols.
		If you want a single list of elements, give a value of 1 - 255 
	*/
	void printStack(int elements = -1, int rows = STACK_SIZE-1, int cols = 1) const;


};