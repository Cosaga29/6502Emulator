#include <iostream>
#include "CPU.hpp"







int main()
{

	CPU ecpu;
	ecpu.printState();

	ecpu.x_reg.gen_reg = 0;

	ecpu.printState();

	ecpu.program_counter.pc_reg &= 0xFF00;

	ecpu.printState();

	ecpu.program_counter.pc_reg_bits.b0 = 1;
	ecpu.program_counter.pc_reg_bits.b15 = 0;

	ecpu.printState();

	ecpu.printStack(-1, 50, 3);

	return 0;
}