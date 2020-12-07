#include "ShaderLib.h"
#include "ShaderChunk.h"

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

    bool ShaderLib::IsValid() const noexcept
    {
        return (mVertexShader != "") && (mFragmentShader != "");
    }

    ShaderLib ShaderLib::basic;
    ShaderLib ShaderLib::lambert;
    ShaderLib ShaderLib::phong;
    ShaderLib ShaderLib::standard;
    ShaderLib ShaderLib::toon;
    ShaderLib ShaderLib::matcap;
    ShaderLib ShaderLib::points;
    ShaderLib ShaderLib::depth;
    ShaderLib ShaderLib::normal;
    ShaderLib ShaderLib::sprite;
    ShaderLib ShaderLib::background;
    ShaderLib ShaderLib::cube;
    ShaderLib ShaderLib::equirect;
    ShaderLib ShaderLib::distanceRGBA;
    ShaderLib ShaderLib::shadow;
    ShaderLib ShaderLib::physical;

    const ShaderLib& ShaderLib::GetBasicShaderLib()
    {
        if (!basic.IsValid())
        {
            basic.mUniforms.MergeUniformsLibs
            (
                6,
                UniformsLib::GetCommonUniformsLib(),
                UniformsLib::GetSpecularmapUniformsLib(),
                UniformsLib::GetEnvmapUniformsLib(),
                UniformsLib::GetAomapUniformsLib(),
                UniformsLib::GetLightmapUniformsLib(),
                UniformsLib::GetFogUniformsLib()
            );
            basic.mVertexShader = ShaderChunk::meshbasic_vert;
            basic.mFragmentShader = ShaderChunk::meshbasic_frag;
        }

        return basic;
    }

    const ShaderLib& ShaderLib::GetLambertShaderLib()
    {
        if (!lambert.IsValid())
        {
            lambert.mUniforms.MergeUniformsLibs
            (
                8,
                UniformsLib::GetCommonUniformsLib(),
                UniformsLib::GetSpecularmapUniformsLib(),
                UniformsLib::GetEnvmapUniformsLib(),
                UniformsLib::GetAomapUniformsLib(),
                UniformsLib::GetLightmapUniformsLib(),
                UniformsLib::GetEmissivemapUniformsLib(),
                UniformsLib::GetFogUniformsLib(),
                UniformsLib::GetLightsUniformsLib()
            );
            lambert.mUniforms.AddUniform("emissive", &Math::Color(0), sizeof(Math::Color));
            lambert.mVertexShader = ShaderChunk::meshlambert_vert;
            lambert.mFragmentShader = ShaderChunk::meshlambert_frag;
        }

        return lambert;
    }

    const ShaderLib& ShaderLib::GetPhongShaderLib()
    {}

    const ShaderLib& ShaderLib::GetStandardShaderLib()
    {}

    const ShaderLib& ShaderLib::GetToonShaderLib()
    {}

    const ShaderLib& ShaderLib::GetMatcapShaderLib()
    {}

    const ShaderLib& ShaderLib::GetPointsShaderLib()
    {}

    const ShaderLib& ShaderLib::GetDepthShaderLib()
    {}

    const ShaderLib& ShaderLib::GetNormalShaderLib()
    {}

    const ShaderLib& ShaderLib::GetSpriteShaderLib()
    {}

    const ShaderLib& ShaderLib::GetBackgroundShaderLib()
    {}

    const ShaderLib& ShaderLib::GetCubeShaderLib()
    {}

    const ShaderLib& ShaderLib::GetEquirectShaderLib()
    {}

    const ShaderLib& ShaderLib::GetDistanceRGBAShaderLib()
    {}

    const ShaderLib& ShaderLib::GetShadowShaderLib()
    {}

    const ShaderLib& ShaderLib::GetPhysicalShaderLib()
    {}
}