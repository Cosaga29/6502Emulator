#include "CPU.hpp"




void CPU::printStack(int elements, int rows, int cols) const
{
	//save cout flags
	std::ios_base::fmtflags prev_flags(std::cout.flags());
	std::cout << std::uppercase;
	std::cout << std::setfill('0');

	if (elements > 0 && elements < 256)
	{
		//print one column number of elements
		for (int i = 0; i < elements; i++)
		{
			std::cout << std::hex << std::setw(4) << i << ": " << std::setw(4) << (int)stack.data[i] << std::dec << "\n";
		}
		std::cout << std::endl;
		return;
	}

	if (rows * cols > 255)
	{
		std::cout << "cannot print that many cols\n" << std::endl;
		return;
	}

	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			std::cout << std::hex << std::setw(4) << ((i * cols) + j) << ": " << std::setw(4) << (int)stack.data[i * cols + j] << std::dec << "\t";
		}
		std::cout << std::endl;
	}

	std::cout.flags(prev_flags); //restore previous cout flags
}


void CPU::printState() const
{
	uint16_t pc = program_counter.pc_reg;
	std::bitset<8> pc_low = 0x00FF & pc;
	std::bitset<8> pc_high = (0xFF00 & pc) >> 8;

	std::cout << "6502 State\n";
	std::cout << "\tRegisters:\n"
		<< "\t\tA \t" << std::bitset<8>(accumulator.gen_reg) << "\n"
		<< "\t\tX: \t" << std::bitset<8>(x_reg.gen_reg) << "\n"
		<< "\t\tY: \t" << std::bitset<8>(y_reg.gen_reg) << "\n"
		<< "\t\tESP: \t" << std::bitset<8>(stack_pointer.gen_reg) << "\n"
		<< "\t\tS: \t" << std::bitset<8>(status_reg.status_reg) << "\n"
		<< "\t\tPC: \t" << pc_high << " " << pc_low << "\n"
		<< std::endl;
}