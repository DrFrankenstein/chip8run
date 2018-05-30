#include "VM.hpp"
#include "Instruction.hpp"

#include <algorithm>
#include <random>

using std::uint8_t;
using std::uint16_t;
using std::copy;
using std::random_device;

namespace Chip8 {

VM::VM()
{
	random_device seeder;
	this->rng.seed(seeder());
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
	// TODO
}

void VM::ldMem(VM::Register end)
{
	// TODO
}

void VM::getDt(VM::Register dst)
{
	this->v[dst] = this->dt;
}

void VM::getK(VM::Register dst)
{
	// TODO
}

void VM::setDt(VM::Register src)
{
	this->dt = this->v[src];
}

void VM::setSt(VM::Register src)
{
	this->st = this->v[src];
}

void VM::addImm(VM::Register dst, VM::Immediate addend)
{
	this->v[dst] += addend;
}

void VM::addReg(VM::Register dst, VM::Register addend)
{
	uint8_t origin = this->v[dst];
	this->v[dst] += this->v[addend];
	this->v[0xF] = this->v[dst] < origin;
}

void VM::addI(VM::Register addend)
{
	this->i += this->v[addend];
}

void VM::sub(VM::Register subtrahend, VM::Register minuend)
{
	this->v[0xF] = this->v[subtrahend] < this->v[minuend];
	this->v[subtrahend] -= this->v[minuend];
}

void VM::subn(VM::Register minuend, VM::Register subtrahend)
{
	this->v[0xF] = this->v[subtrahend] < this->v[minuend];
	this->v[minuend] = this->v[subtrahend] - this->v[minuend];
}

void VM::bitOr(VM::Register dst, VM::Register bits)
{
	this->v[dst] |= this->v[bits];
}

void VM::bitAnd(VM::Register dst, VM::Register mask)
{
	this->v[dst] &= this->v[mask];
}

void VM::bitXor(VM::Register dst, VM::Register value)
{
	this->v[dst] ^= this->v[value];
}

void VM::shr(VM::Register dst)
{
	this->v[0xF] = this->v[dst] & 1;
	this->v[dst] >>= 1;
}

void VM::shl(VM::Register dst)
{
	this->v[0xF] = this->v[dst] & 0x80;
	this->v[dst] <<= 1;
}

void VM::rnd(VM::Register dst, VM::Immediate mask)
{
	this->v[dst] = this->rng() & mask;
}

void VM::drw(VM::Register x, VM::Register y, VM::Parameter count)
{
	// TODO
}

void VM::cls() 
{
	// TODO
}

void VM::ldF(VM::Register value) 
{
	// TODO
}

void VM::ldB(VM::Register value) 
{
	uint8_t n = this->v[value];
	this->mem.set(this->i + 2, static_cast<uint8_t>(n % 10));
	this->mem.set(this->i + 1, static_cast<uint8_t>(n / 10 % 10));
	this->mem.set(this->i, static_cast<uint8_t>(n / 100));
}

void VM::skp(VM::Register key) {}
void VM::sknp(VM::Register key) {}

void VM::illegal(Instruction instruction) {}

}
