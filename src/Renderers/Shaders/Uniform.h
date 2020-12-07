#pragma once

namespace Three::Shader
{
    class Uniform
    {
    public:
        Uniform(size_t size);
        Uniform(const void* const value, size_t size);
    
        ~Uniform() noexcept;

        Uniform(const Uniform& uniform);
        Uniform(Uniform&& uniform);
        Uniform& operator=(const Uniform& uniform);
        Uniform& operator=(Uniform&& uniform);

        template<class T>
        void SetValue(const T& value) noexcept;

        template<class T>
        const T& GetValue() const noexcept;

        size_t GetSize() const noexcept;

        bool GetNeedUpdate() const noexcept;

        void SetNeedUpdate(bool update) noexcept;
    private:
        void* mValue;
        size_t mSize;
        bool mNeedUpdate;
    };
}
#include "Uniform.inl"