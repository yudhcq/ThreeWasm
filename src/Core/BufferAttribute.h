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
        enum DataType
        {
            INT8,
            UINT8,
            INT16,
            UINT16,
            INT32,
            UINT32,
            FLOAT,
            DOUBLE
        };
    public:
        BufferAttribute(DataType dataType = UINT8);
        BufferAttribute(const void* const data, size_t memorySize, uint8_t itemSize, bool normalized = false, DataType dataType = UINT8);
        BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false, DataType dataType = UINT8);
        BufferAttribute(const BufferAttribute& bufferAttribute);
        BufferAttribute& operator=(const BufferAttribute& bufferAttribute);
        void SetUsage(Usage usage);
        void CopyAt
        (
            size_t index1,
            const BufferAttribute& attribute,
            size_t index2
        );
        void CopyArray(const std::vector<uint8_t>& value);
        void CopyArray(const void* const value, size_t memorySize);
        void CopyColorsArray(const std::vector<Color>& ca);
        void CopyVector2sArray(const std::vector<Vector2>& v2a);
        void CopyVector3sArray(const std::vector<Vector3>& v3a);
        void CopyVector4sArray(const std::vector<Vector4>& v4a);
        void Set(const std::vector<uint8_t>& value, size_t offset = 0);
        void Set(const void* const value, size_t memorySize, size_t offset);

    protected:
        template<class T>
        T GetX(size_t index) const;
        template<class T>
        T GetY(size_t index) const;
        template<class T>
        T GetZ(size_t index) const;
        template<class T>
        T GetW(size_t index) const;

        template<class T>
        void SetX(size_t index, T value);
        template<class T>
        void SetY(size_t index, T value);
        template<class T>
        void SetZ(size_t index, T value);
        template<class T>
        void SetW(size_t index, T value);
    public:
        static size_t GetDataTypeByteSize(DataType dataType);
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
        DataType dataType;
    };

    class Int8BufferAttribute : public BufferAttribute
    {
    public:
        Int8BufferAttribute();
        Int8BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        int8_t GetX(size_t index) const;
        int8_t GetY(size_t index) const;
        int8_t GetZ(size_t index) const;
        int8_t GetW(size_t index) const;

        void SetX(size_t index, int8_t value);
        void SetY(size_t index, int8_t value);
        void SetZ(size_t index, int8_t value);
        void SetW(size_t index, int8_t value);
    };
    class Uint8BufferAttribute : public BufferAttribute
    {
    public:
        Uint8BufferAttribute();
        Uint8BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        uint8_t GetX(size_t index) const;
        uint8_t GetY(size_t index) const;
        uint8_t GetZ(size_t index) const;
        uint8_t GetW(size_t index) const;

        void SetX(size_t index, uint8_t value);
        void SetY(size_t index, uint8_t value);
        void SetZ(size_t index, uint8_t value);
        void SetW(size_t index, uint8_t value);
    };
    class Uint8ClampedBufferAttribute : public BufferAttribute
    {
    public:
        Uint8ClampedBufferAttribute();
        Uint8ClampedBufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        uint8_t GetX(size_t index) const;
        uint8_t GetY(size_t index) const;
        uint8_t GetZ(size_t index) const;
        uint8_t GetW(size_t index) const;

        void SetX(size_t index, int8_t uint8_t);
        void SetY(size_t index, int8_t uint8_t);
        void SetZ(size_t index, int8_t uint8_t);
        void SetW(size_t index, int8_t uint8_t);
    };
    class Int16BufferAttribute : public BufferAttribute
    {
    public:
        Int16BufferAttribute();
        Int16BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        int16_t GetX(size_t index) const;
        int16_t GetY(size_t index) const;
        int16_t GetZ(size_t index) const;
        int16_t GetW(size_t index) const;

        void SetX(size_t index, int16_t value);
        void SetY(size_t index, int16_t value);
        void SetZ(size_t index, int16_t value);
        void SetW(size_t index, int16_t value);
    };
    class Uint16BufferAttribute : public BufferAttribute
    {
    public:
        Uint16BufferAttribute();
        Uint16BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        uint16_t GetX(size_t index) const;
        uint16_t GetY(size_t index) const;
        uint16_t GetZ(size_t index) const;
        uint16_t GetW(size_t index) const;

        void SetX(size_t index, uint16_t value);
        void SetY(size_t index, uint16_t value);
        void SetZ(size_t index, uint16_t value);
        void SetW(size_t index, uint16_t value);
    };
    class Int32BufferAttribute : public BufferAttribute
    {
    public:
        Int32BufferAttribute();
        Int32BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        int32_t GetX(size_t index) const;
        int32_t GetY(size_t index) const;
        int32_t GetZ(size_t index) const;
        int32_t GetW(size_t index) const;

        void SetX(size_t index, int32_t value);
        void SetY(size_t index, int32_t value);
        void SetZ(size_t index, int32_t value);
        void SetW(size_t index, int32_t value);
    };
    class Uint32BufferAttribute : public BufferAttribute
    {
    public:
        Uint32BufferAttribute();
        Uint32BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        uint32_t GetX(size_t index) const;
        uint32_t GetY(size_t index) const;
        uint32_t GetZ(size_t index) const;
        uint32_t GetW(size_t index) const;

        void SetX(size_t index, uint32_t value);
        void SetY(size_t index, uint32_t value);
        void SetZ(size_t index, uint32_t value);
        void SetW(size_t index, uint32_t value);
    };
    class Float32BufferAttribute : public BufferAttribute
    {
    public:
        Float32BufferAttribute();
        Float32BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        float GetX(size_t index) const;
        float GetY(size_t index) const;
        float GetZ(size_t index) const;
        float GetW(size_t index) const;

        void SetX(size_t index, float value);
        void SetY(size_t index, float value);
        void SetZ(size_t index, float value);
        void SetW(size_t index, float value);
    };
    class Float64BufferAttribute : public BufferAttribute
    {
    public:
        Float64BufferAttribute();
        Float64BufferAttribute(const std::vector<uint8_t>& data, uint8_t itemSize, bool normalized = false);
        double GetX(size_t index) const;
        double GetY(size_t index) const;
        double GetZ(size_t index) const;
        double GetW(size_t index) const;

        void SetX(size_t index, double value);
        void SetY(size_t index, double value);
        void SetZ(size_t index, double value);
        void SetW(size_t index, double value);
    };
} // namespace Three

#include "BufferAttribute.inl"