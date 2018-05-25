#pragma once

#include <cstdint>

namespace Chip8 {

struct Instruction
{
	std::uint16_t instruction;

	inline std::uint8_t nibble(unsigned idx)
	{
		return this->instruction >> idx * 4 & 0xF;
	}

	inline std::uint8_t byte(unsigned idx)
	{
		return this->instruction >> idx * 8 & 0xFF;
	}

	inline std::uint16_t address()
	{
		return this->instruction & 0xFFF;
	}
};

}
