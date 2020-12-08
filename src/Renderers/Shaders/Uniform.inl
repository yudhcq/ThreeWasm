#include <memory>
#include "Uniform.h"

namespace Three
{
    inline Uniform::Uniform()
    {
    }

    inline Uniform::Uniform(size_t memorySize) :
        mSize(memorySize)
    {
        mValue = malloc(memorySize);
    }

    inline Uniform::Uniform(const void* const value, size_t memorySize) :
        mSize(memorySize)
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

    inline Uniform::Uniform(const Uniform& uniform)
    {
        if (nullptr != mValue)
        {
            free(mValue);
        }
        mValue = malloc(uniform.mSize);
        memcpy(mValue, uniform.mValue, uniform.mSize);
    }

    inline Uniform& Uniform::operator=(const Uniform& uniform)
    {
        if (nullptr != mValue)
        {
            free(mValue);
        }
        mValue = malloc(uniform.mSize);
        memcpy(mValue, uniform.mValue, uniform.mSize);
        mNeedUpdate = true;
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