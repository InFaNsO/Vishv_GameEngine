#ifndef DEFINED_VISHV_GRAPHICS_BUFFER_H
#define DEFINED_VISHV_GRAPHICS_BUFFER_H

#include "Common.h"
#include "Colors.h"

namespace Vishv::Graphics
{
	namespace EffectBufferType
	{
		constexpr uint32_t EBTYPE_TRANSFORM		= 0x1 << 0;
		constexpr uint32_t EBTYPE_LIGHT			= 0x1 << 1;
		constexpr uint32_t EBTYPE_MATERIAL		= 0x1 << 2;
		constexpr uint32_t EBTYPE_OPTIONS		= 0x1 << 3;
		constexpr uint32_t EBTYPE_BONE			= 0x1 << 4;
		constexpr uint32_t EBTYPE_TEXTURING		= 0x1 << 5;
		constexpr uint32_t EBTYPE_PARTICLE		= 0x1 << 6;

		struct TextureingData
		{
			Vishv::Math::Matrix4 wvp;
		};
		struct TransformData					//This should match the constant buffer in the shader
		{
			Vishv::Math::Matrix4 world;
			Vishv::Math::Matrix4 wvp;
			Vishv::Math::Vector4 viewPosition;
		};
		struct OptionsData
		{
			float variable1 = 0.0f;
			float variable2 = 1.0f;
			float variable3 = 0.0f;
			float variable4 = 0.0f;
		};
		struct BoneTransformData
		{
			Vishv::Math::Matrix4 boneTransforms[256];
		};
		struct LightData
		{
			Vishv::Math::Vector3 position_Direction = {0.0f, -1.0f, 0.0f};
			float padding;
			Color ambient = Colors::White;
			Color diffuse = Colors::White;
			Color specular = Colors::White;
		};
		struct MaterialData
		{
			Color ambient = Colors::White;
			Color diffuse = Colors::White;
			Color specular = Colors::White;
			float power = 1.0f;
			float padding[3];
		};

		struct ParticleData
		{
			Math::Matrix4 viewPosition;
			Math::Vector3 cameraPosition;
			Math::Vector3 cameraUp;
			float gravity;
			float padding;
		};
	}

	class EffectBufferData
	{
	public:
		void SetBufferTypes(uint32_t format);
		void SetTextureing(EffectBufferType::TextureingData& td);
		void SetTransform(EffectBufferType::TransformData& td);
		void SetOptions(EffectBufferType::OptionsData& od);
		void SetBones(EffectBufferType::BoneTransformData& btd);
		void SetLight(EffectBufferType::LightData& ld);
		void SetMaterial(EffectBufferType::MaterialData& md);
		void SetParticleData(EffectBufferType::ParticleData& md);

		uint32_t GetFormat();
		EffectBufferType::TextureingData*		GetTextureing();
		EffectBufferType::TransformData*		GetTransform();
		EffectBufferType::OptionsData*			GetOptionsData();
		EffectBufferType::BoneTransformData*	GetBonetransformData();
		EffectBufferType::LightData*			GetLightData();
		EffectBufferType::MaterialData*			GetMaterialData();
		EffectBufferType::ParticleData*			GetParticleData();

		void Terminate();

	private:
		std::unique_ptr<EffectBufferType::TextureingData>		mTextureingData = nullptr;
		std::unique_ptr<EffectBufferType::TransformData>		mTransformData = nullptr;
		std::unique_ptr<EffectBufferType::OptionsData>			mOptionsData = nullptr;
		std::unique_ptr<EffectBufferType::BoneTransformData>	mBoneTransformData = nullptr;
		std::unique_ptr<EffectBufferType::LightData>			mLightsData = nullptr;
		std::unique_ptr<EffectBufferType::MaterialData>			mMaterialData = nullptr;
		std::unique_ptr<EffectBufferType::ParticleData>			mParticleData = nullptr;

	private:
		uint32_t mFormat = 0;

	};

}

#endif // !DEFINED_VISHV_GRAPHICS_BUFFER_H



