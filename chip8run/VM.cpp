#include "VM.hpp"
#include "Instruction.hpp"

#include <algorithm>

using std::uint8_t;
using std::uint16_t;
using std::copy;

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

void VM::run()
{
	this->running = true;

	while (this->running)
	{
		Instruction instruction = this->fetchInstruction();
		this->decode(instruction);
	}
}

void VM::sys(VM::Address address)
{
	// no-op for now
}

void VM::jp(VM::Address address) 
{
	this->pc = address;
}

void VM::jpBased(VM::Address address) 
{
	this->pc = this->v[0] + address;
}

void VM::call(VM::Address address) 
{
	this->sp += 2;
	this->mem.set(this->sp, this->pc);

	this->pc = address;
}

void VM::ret()
{
	this->pc = this->mem.get16(this->sp);
	this->sp -= 2;
}

void VM::seImm(VM::Register reg, VM::Immediate value)
{
	if (this->v[reg] == value)
		this->pc += 2;
}

void VM::seReg(VM::Register left, VM::Register right) 
{
	if (this->v[left] == this->v[right])
		this->pc += 2;
}

void VM::sneImm(VM::Register reg, VM::Immediate value) 
{
	if (this->v[reg] != value)
		this->pc += 2;
}

void VM::sneReg(VM::Register left, VM::Register right) 
{
	if (this->v[left] != this->v[right])
		this->pc += 2;
}

void VM::ldImm(VM::Register dst, VM::Immediate val)
{
	this->v[dst] = val;
}

void VM::ldReg(VM::Register dst, VM::Register src) 
{
	this->v[dst] = this->v[src];
}

void VM::ldI(VM::Address address) 
{
	this->i = address;
}

void VM::storeMem(VM::Register end) 
{
	copy(this->v.begin(), this->v.begin() + end, this->mem.begin8() + this->i);
}

void VM::ldMem(VM::Register end) {}

void VM::getDt(VM::Register dst) {}
void VM::getK(VM::Register dst) {}
void VM::setDt(VM::Register src) {}
void VM::setSt(VM::Register src) {}

void VM::addImm(VM::Register dst, VM::Immediate addend) {}
void VM::addReg(VM::Register dst, VM::Register addend) {}
void VM::addI(VM::Register addend) {}
void VM::sub(VM::Register subtrahend, VM::Register minuend) {}
void VM::subn(VM::Register minuend, VM::Register subtrahend) {}
void VM::bitOr(VM::Register dst, VM::Register bits) {}
void VM::bitAnd(VM::Register dst, VM::Register mask) {}
void VM::bitXor(VM::Register dst, VM::Register value) {}
void VM::shr(VM::Register dst, VM::Register shift) {}
void VM::shl(VM::Register dst, VM::Register shift) {}

void VM::rnd(VM::Register dst, VM::Immediate mask) {}

void VM::drw(VM::Register x, VM::Register y, VM::Parameter count) {}
void VM::cls() {}
void VM::ldF(VM::Register value) {}
void VM::ldB(VM::Register value) {}

void VM::skp(VM::Register key) {}
void VM::sknp(VM::Register key) {}

void VM::illegal(Instruction instruction) {}

}
