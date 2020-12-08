#pragma once
#include <vector>

namespace Three
{
	class BufferAttribute
	{
	public:
		BufferAttribute(const std::vector<uint8_t>& array, uint8_t itemSize, bool normalized);
	public:
		std::string name;
		std::vector<uint8_t> array;
		uint8_t itemSize;
	};
} // namespace Three