#include "ShaderLib.h"

namespace Three::Shader
{
    ShaderLib::ShaderLib()
    {}

    UniformsLib& ShaderLib::Uniforms() noexcept
    {
        return mUniforms;
    }

    const UniformsLib& ShaderLib::Uniforms() const noexcept
    {
        return mUniforms;
    }

    const std::string& ShaderLib::GetVertexShader() const noexcept
    {
        return mVertexShader;
    }

    void ShaderLib::SetVertexShader(const std::string& shaderSrc) noexcept
    {
        mVertexShader = shaderSrc;
    }

    const std::string& ShaderLib::GetFragmentShader() const noexcept
    {
        return mFragmentShader;
    }

    void ShaderLib::SetFragmentShader(const std::string& shaderSrc) noexcept
    {
        mFragmentShader = shaderSrc;
    }

    bool ShaderLib::isValid() const noexcept
    {
        return (mVertexShader != "") && (mFragmentShader != "");
    }

}