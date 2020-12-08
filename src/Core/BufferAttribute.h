#pragma once
#include <vector>
#include "../constants.h"

namespace Three
{
	class Color;
	class Vector2;
	class Vector3;
	class Vector4;
	class BufferAttribute
	{
	public:
		BufferAttribute(const std::vector<uint8_t>& array, uint8_t itemSize, bool normalized);
		BufferAttribute(const BufferAttribute& bufferAttribute);
		BufferAttribute& operator=(const BufferAttribute& bufferAttribute);
		void SetUsage(Usage usage);
		void CopyAt
		(
			size_t index1,
			const BufferAttribute& attribute,
			size_t index2
		);
		void CopyArray(const std::vector<uint8_t>& a);
		void CopyColorsArray(const std::vector<Color>& ca);
		void CopyVector2sArray(const std::vector<Vector2>& v2a);
		void CopyVector3sArray(const std::vector<Vector3>& v3a);
		void CopyVector4sArray(const std::vector<Vector4>& v4a);
		void Set(const std::vector<uint8_t>& value, size_t offset = 0);

	public:
		std::string name;
		std::vector<uint8_t> array;
		uint8_t itemSize;
		Usage usage;
		struct Range
		{
			size_t offset;
			size_t count;
		} updateRange;
		size_t version;
		bool normalized;
		bool needsUpdate;
		size_t count;
	};
} // namespace Three