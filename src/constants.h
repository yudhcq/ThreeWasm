#pragma once
#include <stdint.h>

namespace Three
{
	enum class MOUSE: uint8_t
	{
		LEFT,
		MIDDLE,
		RIGHT,
		ROTATE,
		DOLLY,
		PAN
	};

	enum class TOUCH: uint8_t
	{
		ROTATE,
		PAN,
		DOLLY_PAN,
		DOLLY_ROTATE
	};

	enum CullFace
	{
		CullFaceNone,
		CullFaceBack,
		CullFaceFront,
		CullFaceFrontBack
	};

	enum  FrontFaceDirection
	{
		FrontFaceDirectionCW,
		FrontFaceDirectionCCW
	};

	enum ShadowMapType
	{
		BasicShadowMap,
		PCFShadowMap,
		PCFSoftShadowMap,
		VSMShadowMap
	};

	enum Side
	{
		FrontSide,
		BackSide,
		DoubleSide
	};

	enum Shading
	{
		FlatShading = 1,
		SmoothShading
	};

	enum Colors
	{
		NoColors,
		FaceColors,
		VertexColors
	};

	enum Blending
	{
		NoBlending,
		NormalBlending,
		AdditiveBlending,
		SubtractiveBlending,
		MultiplyBlending,
		CustomBlending
	};

	enum BlendingEquation
	{
		AddEquation = 100,
		SubtractEquation,
		ReverseSubtractEquation,
		MinEquation,
		MaxEquation
	};

	enum BlendingDstFactor
	{
		ZeroFactor = 200,
		OneFactor,
		SrcColorFactor,
		OneMinusSrcColorFactor,
		SrcAlphaFactor,
		OneMinusSrcAlphaFactor,
		DstAlphaFactor,
		OneMinusDstAlphaFactor,
		DstColorFactor,
		OneMinusDstColorFactor
	};

	enum BlendingSrcFactor
	{
		SrcAlphaSaturateFactor = 210
	};

	enum DepthModes
	{
		NeverDepth,
		AlwaysDepth,
		LessDepth,
		LessEqualDepth,
		EqualDepth,
		GreaterEqualDepth,
		GreaterDepth,
		NotEqualDepth
	};

	enum Combine
	{
		MultiplyOperation,
		MixOperation,
		AddOperation
	};

	enum ToneMapping
	{
		NoToneMapping,
		LinearToneMapping,
		ReinhardToneMapping,
		Uncharted2ToneMapping,
		CineonToneMapping,
		ACESFilmicToneMapping
	};

	enum Mapping
	{
		UVMapping = 300,
		CubeReflectionMapping,
		CubeRefractionMapping,
		EquirectangularReflectionMapping,
		EquirectangularRefractionMapping,
		SphericalReflectionMapping,
		CubeUVReflectionMapping,
		CubeUVRefractionMapping
	};

	enum Wrapping
	{
		RepeatWrapping = 1000,
		ClampToEdgeWrapping,
		MirroredRepeatWrapping
	};

	enum TextureFilter
	{
		NearestFilter = 1003,
		NearestMipMapNearestFilter,
		NearestMipMapLinearFilter,
		LinearFilter,
		LinearMipMapNearestFilter,
		LinearMipMapLinearFilter
	};

	enum TextureDataType
	{
		UnsignedByteType = 1009,
		ByteType,
		ShortType,
		UnsignedShortType,
		IntType,
		UnsignedIntType,
		FloatType,
		HalfFloatType
	};

	enum PixelType
	{
		UnsignedShort4444Type = 1017,
		UnsignedShort5551Type,
		UnsignedShort565Type,
		UnsignedInt248Type
	};

	enum PixelFormat
	{
		AlphaFormat = 1021,
		RGBFormat,
		RGBAFormat,
		LuminanceFormat,
		LuminanceAlphaFormat,
		RGBEFormat,
		DepthFormat,
		DepthStencilFormat,
		RedFormat
	};

	enum CompressedPixelFormat
	{
		RGB_S3TC_DXT1_Format = 33776,
		RGBA_S3TC_DXT1_Format,
		RGBA_S3TC_DXT3_Format,
		RGBA_S3TC_DXT5_Format,
		RGB_PVRTC_4BPPV1_Format = 35840,
		RGB_PVRTC_2BPPV1_Format,
		RGBA_PVRTC_4BPPV1_Format,
		RGBA_PVRTC_2BPPV1_Format,
		RGB_ETC1_Format = 36196,
		RGBA_ASTC_4x4_Format = 37808,
		RGBA_ASTC_5x4_Format,
		RGBA_ASTC_5x5_Format,
		RGBA_ASTC_6x5_Format,
		RGBA_ASTC_6x6_Format,
		RGBA_ASTC_8x5_Format,
		RGBA_ASTC_8x6_Format,
		RGBA_ASTC_8x8_Format,
		RGBA_ASTC_10x5_Format,
		RGBA_ASTC_10x6_Format,
		RGBA_ASTC_10x8_Format,
		RGBA_ASTC_10x10_Format,
		RGBA_ASTC_12x10_Format,
		RGBA_ASTC_12x12_Format
	};

	enum AnimationActionLoopStyles
	{
		LoopOnce = 2200,
		LoopRepeat,
		LoopPingPong
	};

	enum InterpolationModes
	{
		InterpolateDiscrete= 2300,
		InterpolateLinear,
		InterpolateSmooth
	};

	enum InterpolationEndingModes
	{
		ZeroCurvatureEnding = 2400,
		ZeroSlopeEnding,
		WrapAroundEnding
	};

	enum TrianglesDrawModes
	{
		TrianglesDrawMode,
		TriangleStripDrawMode,
		TriangleFanDrawMode
	};

	enum TextureEncoding
	{
		LinearEncoding = 3000,
		sRGBEncoding,
		GammaEncoding = 3007,
		RGBEEncoding = 3002,
		LogLuvEncoding,
		RGBM7Encoding,
		RGBM16Encoding,
		RGBDEncoding
	};

	enum DepthPackingStrategies
	{
		BasicDepthPacking = 3200,
		RGBADepthPacking
	};

	enum NormalMapTypes
	{
		TangentSpaceNormalMap,
		ObjectSpaceNormalMap
	};

	enum StencilOp
	{
		ZeroStencilOp = 0,
		KeepStencilOp = 7680,
		ReplaceStencilOp,
		IncrementStencilOp,
		DecrementStencilOp,
		IncrementWrapStencilOp = 34055,
		DecrementWrapStencilOp,
		InvertStencilOp = 5386
	};

	enum StencilFunc
	{
		NeverStencilFunc = 512,
		LessStencilFunc,
		EqualStencilFunc,
		LessEqualStencilFunc,
		GreaterStencilFunc,
		NotEqualStencilFunc,
		GreaterEqualStencilFunc,
		AlwaysStencilFunc
	};

	enum Usage
	{
		StaticDrawUsage = 35044,
		DynamicDrawUsage = 35048,
		StreamDrawUsage = 35040,
		StaticReadUsage = 35045,
		DynamicReadUsage = 35049,
		StreamReadUsage = 35041,
		StaticCopyUsage = 35046,
		DynamicCopyUsage = 35050,
		StreamCopyUsage = 35042
	};
}
