#ifndef INCLUDED_VISHV_GRAPHICS_EFFECTSCONSTANTBUFFER_H
#define INCLUDED_VISHV_GRAPHICS_EFFECTSCONSTANTBUFFER_H

#include "Common.h"
#include "EffectsBufferData.h"
#include "ConstantBuffer.h"

namespace Vishv::Graphics
{
	namespace ShaderType
	{
		constexpr uint32_t EF_VERTEX = 0x1 << 0;
		constexpr uint32_t EF_PIXEL = 0x1 << 1;
		constexpr uint32_t EF_GEOMETRY = 0x1 << 2;
	}

	class EffectsConstantBuffer
	{
	public:
		void Intialize(uint32_t dataFormat, uint32_t shaderFormat);

		void Set(EffectBufferData& data);
		void Bind();

		void Terminate();

		uint32_t GetFormat() { return mFormat; }
	private:
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::TextureingData>>		mTextureingBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::TransformData>>		mTransformBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::OptionsData>>			mOptionsBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::BoneTransformData>>	mBoneTransformBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::LightData>>			mLightsBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::MaterialData>>		mMaterialBuffer = nullptr;
		std::unique_ptr<TypedConstantBuffer<EffectBufferType::ParticleData>>		mParticleBuffer = nullptr;

	private:
		void Init();
		uint32_t mFormat = 0;
		uint32_t mDataFormat = 0;
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_EFFECTSCONSTANTBUFFER_H

