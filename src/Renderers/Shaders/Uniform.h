#pragma once

namespace Three
{
    class Uniform
    {
    public:
        Uniform();
        Uniform(size_t size);
        Uniform(const void* const value, size_t size);
    
        ~Uniform() noexcept;

        Uniform(const Uniform& uniform);
        Uniform(Uniform&& uniform);
        Uniform& operator=(const Uniform& uniform);
        Uniform& operator=(Uniform&& uniform);

        template<class T>
        void SetValue(const T& value) noexcept
        {
            if (sizeof(T) == mSize)
            {
                memcpy(mValue, &value, mSize);
            }
        }

        template<class T>
        const T& GetValue() const noexcept
        {
            return *reinterpret_cast<T*>(mValue);
        }

        size_t GetSize() const noexcept;

        bool GetNeedUpdate() const noexcept;

        void SetNeedUpdate(bool update) noexcept;
    private:
        void* mValue = nullptr;
        size_t mSize = 0;
        bool mNeedUpdate = true;
    };
}
#include "Uniform.inl"