#pragma once

#include <cstdint>

namespace Chip8 {

struct Instruction
{
	using Operation = std::uint8_t;
	using Register = std::uint8_t;
	using Parameter = std::uint8_t;
	using Immediate = std::uint8_t;
	using Address = std::uint16_t;

	std::uint16_t instruction;

	inline Operation op()
	{
		return this->nibble<3>();
	}

	inline Register reg1()
	{
		return this->nibble<2>();
	}

	inline Register reg2()
	{
		return this->nibble<1>();
	}

	inline Parameter parameter()
	{
		return this->nibble<0>();
	}

	inline Immediate immediate()
	{
		return this->byte<0>();
	}

	inline Address address()
	{
		return this->instruction & 0xFFF;
	}

private:
	template<unsigned Index>
	inline std::uint8_t nibble()
	{
		return this->instruction >> Index * 4 & 0xF;
	}

	template<unsigned Index>
	inline std::uint8_t byte()
	{
		return this->instruction >> Index * 8 & 0xFF;
	}
};

}
