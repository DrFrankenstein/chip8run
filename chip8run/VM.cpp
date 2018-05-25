#include "VM.h"
#include "Instruction.h"

namespace Chip8 {

VM::VM()
{
}

Instruction VM::fetchInstruction()
{
	Instruction instruction { this->mem.get16(this->pc) };
	this->pc += 2;
	return instruction;
}

void VM::execute(Instruction instruction)
{
	switch (instruction.nibble(3))
	{
	case 0:
	{
		switch (instruction.address())
		{
		case 0xE0:
			this->cls(instruction);
			break;

		case 0xEE:
			this->ret(instruction);
			break;

		default:
			this->sys(instruction);
			break;
		}
	}
	break;

	case 1:
		this->jp(instruction);
		break;

	case 2:
		this->call(instruction);
		break;


	}
}

}
