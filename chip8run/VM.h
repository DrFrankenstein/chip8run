#pragma once

#include "Memory.h"
#include "Instruction.h"

#include <cstdint>
#include <array>

namespace Chip8 {

class VM
{
	std::array<std::uint8_t, 16> v {};
	std::uint16_t i {}, pc {0x200};
	std::uint8_t sp {}, dt {}, st {};
	Memory<0x1000> mem {};


public:
	VM();

	Instruction fetchInstruction();

private:
	void execute(Instruction instruction);

	void sys(Instruction instruction);
	void cls(Instruction instruction);
	void ret(Instruction instruction);
	void jp(Instruction instruction);
	void call(Instruction instruction);
	
	void seImm(Instruction instruction);
	void sneImm(Instruction instruction);
	void seReg(Instruction instruction);

	void ldImm(Instruction instruction);
	void ldReg(Instruction instruction);

	void addImm(Instruction instruction);
	void orReg(Instruction instruction);
	void andReg(Instruction instruction);
	void xorReg(Instruction instruction);
};

}
