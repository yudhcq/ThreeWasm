#pragma once
#include "UniformsLib.h"

namespace Three::Shader
{
    class ShaderLib
    {
    public:
        ShaderLib();

        UniformsLib& Uniforms() noexcept;
        const UniformsLib& Uniforms() const noexcept;

        const std::string& GetVertexShader() const noexcept;
        void SetVertexShader(const std::string& shaderSrc) noexcept;

        const std::string& GetFragmentShader() const noexcept;
        void SetFragmentShader(const std::string& shaderSrc) noexcept;

        bool IsValid() const noexcept;

    public:
        static const ShaderLib& GetBasicShaderLib();
        static const ShaderLib& GetLambertShaderLib();
        static const ShaderLib& GetPhongShaderLib();
        static const ShaderLib& GetStandardShaderLib();
        static const ShaderLib& GetToonShaderLib();
        static const ShaderLib& GetMatcapShaderLib();
        static const ShaderLib& GetPointsShaderLib();
        static const ShaderLib& GetDepthShaderLib();
        static const ShaderLib& GetNormalShaderLib();
        static const ShaderLib& GetSpriteShaderLib();
        static const ShaderLib& GetBackgroundShaderLib();
        static const ShaderLib& GetCubeShaderLib();
        static const ShaderLib& GetEquirectShaderLib();
        static const ShaderLib& GetDistanceRGBAShaderLib();
        static const ShaderLib& GetShadowShaderLib();
        static const ShaderLib& GetPhysicalShaderLib();
    private:

        static ShaderLib basic;
        static ShaderLib lambert;
        static ShaderLib phong;
        static ShaderLib standard;
        static ShaderLib toon;
        static ShaderLib matcap;
        static ShaderLib points;
        static ShaderLib depth;
        static ShaderLib normal;
        static ShaderLib sprite;
        static ShaderLib background;
        static ShaderLib cube;
        static ShaderLib equirect;
        static ShaderLib distanceRGBA;
        static ShaderLib shadow;
        static ShaderLib physical;

    private:
        UniformsLib mUniforms;
        std::string mVertexShader;
        std::string mFragmentShader;
    };
}
