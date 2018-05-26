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
	using Address = Instruction::Address;
	using Register = Instruction::Register;
	using Immediate = Instruction::Immediate;
	using Parameter = Instruction::Parameter;

	void execute(Instruction instruction);

	void sys(Address address);
	void jp(Address address);
	void jpBased(Address address);
	void call(Address address);
	void ret();
	
	void seImm(Register reg, Immediate value);
	void seReg(Register left, Register right);
	void sneImm(Register reg, Immediate value);
	void sneReg(Register left, Register right);

	void ldImm(Register dst, Immediate val);
	void ldReg(Register dst, Register src);
	void ldI(Address address);
	void storeMem(Register end);
	void ldMem(Register end);

	void getDt(Register dst);
	void getK(Register dst);
	void setDt(Register src);
	void setSt(Register src);

	void addImm(Register dst, Immediate addend);
	void addReg(Register dst, Register addend);
	void addI(Register addend);
	void sub(Register subtrahend, Register minuend);
	void subn(Register minuend, Register subtrahend);
	void bitOr(Register dst, Register bits);
	void bitAnd(Register dst, Register mask);
	void bitXor(Register dst, Register value);
	void shr(Register dst, Register shift);
	void shl(Register dst, Register shift);

	void rnd(Register dst, Immediate mask);

	void drw(Register x, Register y, Parameter count);
	void cls();
	void ldF(Register value);
	void ldB(Register value);

	void skp(Register key);
	void sknp(Register key);

	void illegal(Instruction instruction);
};

}
