#pragma once

#include "Instruction.hpp"

namespace Chip8 {

template <typename Impl>
class InstructionDecoder
{
	using Address = Instruction::Address;
	using Register = Instruction::Register;
	using Immediate = Instruction::Immediate;
	using Parameter = Instruction::Parameter;

	Impl& impl()
	{
		return *static_cast<Impl*>(this);
	}

protected:
	void decode(Instruction instruction)
	{
		switch (instruction.op())
		{
		case 0:
			switch (instruction.address())
			{
			case 0xE0:
				impl().cls();
				break;

			case 0xEE:
				impl().ret();
				break;

			default:
				impl().sys(instruction.address());
				break;
			}
			break;

		case 1:
			impl().jp(instruction.address());
			break;

		case 2:
			impl().call(instruction.address());
			break;

		case 3:
			impl().seImm(instruction.reg1(), instruction.immediate());
			break;

		case 4:
			impl().sneImm(instruction.reg1(), instruction.immediate());
			break;

		case 5:
			impl().seReg(instruction.reg1(), instruction.reg2());
			break;

		case 6:
			impl().ldImm(instruction.reg1(), instruction.immediate());
			break;

		case 7:
			impl().addImm(instruction.reg1(), instruction.immediate());
			break;

		case 8:
			switch (instruction.parameter())
			{
			case 0:
				impl().ldReg(instruction.reg1(), instruction.reg2());
				break;

			case 1:
				impl().bitOr(instruction.reg1(), instruction.reg2());
				break;

			case 2:
				impl().bitAnd(instruction.reg1(), instruction.reg2());
				break;

			case 3:
				impl().bitXor(instruction.reg1(), instruction.reg2());
				break;

			case 4:
				impl().addReg(instruction.reg1(), instruction.reg2());
				break;

			case 5:
				impl().sub(instruction.reg1(), instruction.reg2());
				break;

			case 6:
				impl().shr(instruction.reg1(), instruction.reg2());
				break;

			case 7:
				impl().subn(instruction.reg1(), instruction.reg2());
				break;

			case 0xE:
				impl().shl(instruction.reg1(), instruction.reg2());
				break;

			default:
				impl().illegal(instruction);
				break;
			}
			break;

		case 9:
			impl().sneReg(instruction.reg1(), instruction.reg2());
			break;

		case 0xA:
			impl().ldI(instruction.address());
			break;

		case 0xB:
			impl().jpBased(instruction.address());
			break;

		case 0xC:
			impl().rnd(instruction.reg1(), instruction.immediate());
			break;

		case 0xD:
			impl().drw(instruction.reg1(), instruction.reg2(), instruction.parameter());
			break;

		case 0xE:
			switch (instruction.immediate())
			{
			case 0x9E:
				impl().skp(instruction.reg1());
				break;

			case 0xA1:
				impl().sknp(instruction.reg1());
				break;

			default:
				impl().illegal(instruction);
				break;
			}
			break;

		case 0xF:
			switch (instruction.immediate())
			{
			case 0x07:
				impl().getDt(instruction.reg1());
				break;

			case 0x0A:
				impl().getK(instruction.reg1());
				break;

			case 0x15:
				impl().setDt(instruction.reg1());
				break;

			case 0x18:
				impl().setSt(instruction.reg1());
				break;

			case 0x1E:
				impl().addI(instruction.reg1());
				break;

			case 0x29:
				impl().ldF(instruction.reg1());
				break;

			case 0x33:
				impl().ldB(instruction.reg1());
				break;

			case 0x55:
				impl().storeMem(instruction.reg1());
				break;

			case 0x65:
				impl().ldMem(instruction.reg1());
				break;

			default:
				impl().illegal(instruction);
			}
			break;

		default:
			impl().illegal(instruction);
			break;
		}
	}
};

}