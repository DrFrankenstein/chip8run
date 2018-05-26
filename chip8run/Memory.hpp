#pragma once

#include <cstddef>
#include <cstdint>

namespace Chip8 {

template<std::size_t Size>
class Memory
{
	std::uint8_t data[Size] {};

public:
	std::uint8_t* begin8()
	{
		return this->data;
	}

	std::uint8_t* end8()
	{
		return this->data + Size;
	}

	std::uint16_t* begin16()
	{
		return reinterpret_cast<std::uint16_t>(this->begin8());
	}

	std::uint16_t* end16()
	{
		return reinterpret_cast<std::uint16_t>(this->end8());
	}

	std::uint8_t get8(std::uint16_t address)
	{
		return this->data[address];
	}

	std::uint16_t get16(std::uint16_t address)
	{
		return *reinterpret_cast<std::uint16_t*>(this->data + address);
	}
};

}
