#include "VM.hpp"
#include "Instruction.hpp"

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
}

void VM::jp(VM::Address address) {}
void VM::jpBased(VM::Address address) {}
void VM::call(VM::Address address) {}
void VM::ret() {}

void VM::seImm(VM::Register reg, VM::Immediate value) {}
void VM::seReg(VM::Register left, VM::Register right) {}
void VM::sneImm(VM::Register reg, VM::Immediate value) {}
void VM::sneReg(VM::Register left, VM::Register right) {}

void VM::ldImm(VM::Register dst, VM::Immediate val) {}
void VM::ldReg(VM::Register dst, VM::Register src) {}
void VM::ldI(VM::Address address) {}
void VM::storeMem(VM::Register end) {}
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
