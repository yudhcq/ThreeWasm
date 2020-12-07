#include <memory>
#include "Uniform.h"

namespace Three::Shader
{
    inline Uniform::Uniform(size_t memorySize): 
        mSize(memorySize),
        mNeedUpdate(true)
    {
        mValue = malloc(memorySize);
    }

    inline Uniform::Uniform(const void* const value, size_t memorySize): 
        mSize(memorySize),
        mNeedUpdate(true)
    {
        mValue = malloc(memorySize);
        memcpy(mValue, value, memorySize);
    }

    inline Uniform::~Uniform() noexcept
    {
        if (nullptr != mValue)
        {
            free(mValue);
            mValue = nullptr;
        }
    }

    inline Uniform::Uniform(Uniform&& uniform)
    {
        if (nullptr != uniform.mValue) 
        {
            if (nullptr != mValue)
            {
                free(mValue);
            }
            mValue = uniform.mValue;
            uniform.mValue = nullptr;
        }
    }


    inline Uniform::Uniform(const Uniform &uniform)
    {
        mValue = malloc(uniform.mSize);
        memcpy(mValue, uniform.mValue, uniform.mSize);
    }

    inline Uniform& Uniform::operator=(const Uniform& uniform)
    {
        mValue = malloc(uniform.mSize);
        memcpy(mValue, uniform.mValue, uniform.mSize);
        return *this;
    }

    inline Uniform& Uniform::operator=(Uniform&& uniform)
    {
        if (nullptr != uniform.mValue)
        {
            if (nullptr != mValue)
            {
                free(mValue);
            }
            mValue = uniform.mValue;
            uniform.mValue = nullptr;
        }
        return *this;
    }

    template<class T>
    inline void Uniform::SetValue(const T& value)
    {
        if (sizeof(T) == mSize)
        {
            memcpy(mValue, &value, mSize);
        }
    }

    template<class T>
    inline const T& Uniform::GetValue() const noexcept
    {
        return *mValue;
    }

    inline size_t Uniform::GetSize() const noexcept
    {
        return mSize;
    }

    inline bool Uniform::GetNeedUpdate() const noexcept
    {
        return mNeedUpdate;
    }

    inline void Uniform::SetNeedUpdate(bool update) noexcept
    {
        mNeedUpdate = update;
    }
}