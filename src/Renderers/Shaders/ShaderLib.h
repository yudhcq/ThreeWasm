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

        bool isValid() const noexcept;

    public:
        static ShaderLib GetBasic;
        static ShaderLib GetLambert;
        static ShaderLib GetPhong;
        static ShaderLib GetStandard;
        static ShaderLib GetToon;
        static ShaderLib GetMatcap;
        static ShaderLib GetPoints;
        static ShaderLib GetDepth;
        static ShaderLib GetNormal;
        static ShaderLib GetSprite;
        static ShaderLib GetBackground;
        static ShaderLib GetCube;
        static ShaderLib GetEquirect;
        static ShaderLib GetDistanceRGBA;
        static ShaderLib GetShadow;
        static ShaderLib GetPhysical;
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
