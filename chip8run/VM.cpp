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
	switch (instruction.op())
	{
	case 0:
		switch (instruction.address())
		{
		case 0xE0:
			this->cls();
			break;

		case 0xEE:
			this->ret();
			break;

		default:
			this->sys(instruction.address());
			break;
		}
		break;

	case 1:
		this->jp(instruction.address());
		break;

	case 2:
		this->call(instruction.address());
		break;

	case 3:
		this->seImm(instruction.reg1(), instruction.immediate());
		break;

	case 4:
		this->sneImm(instruction.reg1(), instruction.immediate());
		break;

	case 5:
		this->seReg(instruction.reg1(), instruction.reg2());
		break;

	case 6:
		this->ldImm(instruction.reg1(), instruction.immediate());
		break;

	case 7:
		this->addImm(instruction.reg1(), instruction.immediate());
		break;

	case 8:
		switch (instruction.parameter())
		{
		case 0:
			this->ldReg(instruction.reg1(), instruction.reg2());
			break;

		case 1:
			this->bitOr(instruction.reg1(), instruction.reg2());
			break;

		case 2:
			this->bitAnd(instruction.reg1(), instruction.reg2());
			break;

		case 3:
			this->bitXor(instruction.reg1(), instruction.reg2());
			break;

		case 4:
			this->addReg(instruction.reg1(), instruction.reg2());
			break;

		case 5:
			this->sub(instruction.reg1(), instruction.reg2());
			break;

		case 6:
			this->shr(instruction.reg1(), instruction.reg2());
			break;

		case 7:
			this->subn(instruction.reg1(), instruction.reg2());
			break;

		case 0xE:
			this->shl(instruction.reg1(), instruction.reg2());
			break;

		default:
			this->illegal(instruction);
			break;
		}
		break;

	case 9:
		this->sneReg(instruction.reg1(), instruction.reg2());
		break;

	case 0xA:
		this->ldI(instruction.address());
		break;

	case 0xB:
		this->jpBased(instruction.address());
		break;

	case 0xC:
		this->rnd(instruction.reg1(), instruction.immediate());
		break;

	case 0xD:
		this->drw(instruction.reg1(), instruction.reg2(), instruction.parameter());
		break;

	case 0xE:
		switch (instruction.immediate())
		{
		case 0x9E:
			this->skp(instruction.reg1());
			break;

		case 0xA1:
			this->sknp(instruction.reg1());
			break;

		default:
			this->illegal(instruction);
			break;
		}
		break;

	case 0xF:
		switch (instruction.immediate())
		{
		case 0x07:
			this->getDt(instruction.reg1());
			break;

		case 0x0A:
			this->getK(instruction.reg1());
			break;

		case 0x15:
			this->setDt(instruction.reg1());
			break;

		case 0x18:
			this->setSt(instruction.reg1());
			break;

		case 0x1E:
			this->addI(instruction.reg1());
			break;

		case 0x29:
			this->ldF(instruction.reg1());
			break;

		case 0x33:
			this->ldB(instruction.reg1());
			break;

		case 0x55:
			this->storeMem(instruction.reg1());
			break;

		case 0x65:
			this->ldMem(instruction.reg1());
			break;

		default:
			this->illegal(instruction);
		}
		break;

	default:
		this->illegal(instruction);
		break;
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
