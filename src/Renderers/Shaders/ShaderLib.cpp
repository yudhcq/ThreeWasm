#include "ShaderLib.h"
#include "ShaderChunk.h"

namespace Three
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
            const Color _emissive;
            lambert.mUniforms.AddUniform("emissive", &_emissive, sizeof(Color));
            lambert.mVertexShader = ShaderChunk::meshlambert_vert;
            lambert.mFragmentShader = ShaderChunk::meshlambert_frag;
        }

        return lambert;
    }

    const ShaderLib& ShaderLib::GetPhongShaderLib()
    {
        return phong;
    }

    const ShaderLib& ShaderLib::GetStandardShaderLib()
    {
        return standard;
    }

    const ShaderLib& ShaderLib::GetToonShaderLib()
    {
        return toon;
    }

    const ShaderLib& ShaderLib::GetMatcapShaderLib()
    {
        return matcap;
    }

    const ShaderLib& ShaderLib::GetPointsShaderLib()
    {
        return points;
    }

    const ShaderLib& ShaderLib::GetDepthShaderLib()
    {
        return depth;
    }

    const ShaderLib& ShaderLib::GetNormalShaderLib()
    {
        return normal;
    }

    const ShaderLib& ShaderLib::GetSpriteShaderLib()
    {
        return sprite;
    }

    const ShaderLib& ShaderLib::GetBackgroundShaderLib()
    {
        return background;
    }

    const ShaderLib& ShaderLib::GetCubeShaderLib()
    {
        return cube;
    }

    const ShaderLib& ShaderLib::GetEquirectShaderLib()
    {
        return equirect;
    }

    const ShaderLib& ShaderLib::GetDistanceRGBAShaderLib()
    {
        return distanceRGBA;
    }

    const ShaderLib& ShaderLib::GetShadowShaderLib()
    {
        return shadow;
    }

    const ShaderLib& ShaderLib::GetPhysicalShaderLib()
    {
        return physical;
    }
}