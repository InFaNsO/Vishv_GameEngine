#include "Precompiled.h"
#include "EffectsBufferData.h"

using namespace Vishv::Graphics;

void Vishv::Graphics::EffectBufferData::SetBufferTypes(uint32_t format)
{
	mFormat = format;

	if (mFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformData = std::make_unique<EffectBufferType::TransformData>();
	if (mFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsData = std::make_unique<EffectBufferType::LightData>();
	if (mFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialData = std::make_unique<EffectBufferType::MaterialData>();
	if (mFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsData = std::make_unique<EffectBufferType::OptionsData>();
	if (mFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformData = std::make_unique<EffectBufferType::BoneTransformData>();
	if (mFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingData = std::make_unique<EffectBufferType::TextureingData>();
	if (mFormat & EffectBufferType::EBTYPE_PARTICLE)
		mParticleData = std::make_unique<EffectBufferType::ParticleData>();
}

void Vishv::Graphics::EffectBufferData::SetTextureing(EffectBufferType::TextureingData& td)
{
	VISHVASSERT(mTextureingData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mTextureingData.get() = td;
}

void Vishv::Graphics::EffectBufferData::SetTransform(EffectBufferType::TransformData & td)
{
	VISHVASSERT(mTransformData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mTransformData.get() = td;
}
void Vishv::Graphics::EffectBufferData::SetOptions(EffectBufferType::OptionsData& od)
{
	VISHVASSERT(mOptionsData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mOptionsData.get() = od;
}
void Vishv::Graphics::EffectBufferData::SetBones(EffectBufferType::BoneTransformData& btd)
{
	VISHVASSERT(mBoneTransformData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mBoneTransformData.get() = btd;
}
void Vishv::Graphics::EffectBufferData::SetLight(EffectBufferType::LightData& ld)
{
	VISHVASSERT(mLightsData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mLightsData.get() = ld;
}
void Vishv::Graphics::EffectBufferData::SetMaterial(EffectBufferType::MaterialData& md)
{
	VISHVASSERT(mMaterialData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mMaterialData.get() = md;
}
void Vishv::Graphics::EffectBufferData::SetParticleData(EffectBufferType::ParticleData& md)
{
	VISHVASSERT(mParticleData != nullptr, "[EffectBufferData] trying to set wrong value");
	*mParticleData.get() = md;
}


uint32_t Vishv::Graphics::EffectBufferData::GetFormat()
{
	VISHVASSERT(mFormat != 0, "[EffectBufferData] buffer data not initalized and format not get");
	return mFormat;
}
EffectBufferType::TextureingData * Vishv::Graphics::EffectBufferData::GetTextureing()
{
	VISHVASSERT(mTextureingData != nullptr, "[EffectBufferData] trying to get wrong value");
	return mTextureingData.get();
}
EffectBufferType::TransformData * Vishv::Graphics::EffectBufferData::GetTransform()
{
	VISHVASSERT(mTransformData != nullptr, "[EffectBufferData] trying to get wrong value");
	return mTransformData.get();
}
EffectBufferType::OptionsData * Vishv::Graphics::EffectBufferData::GetOptionsData()
{
	VISHVASSERT(mOptionsData != nullptr, "[EffectBufferData] trying to get wrong value");
	return mOptionsData.get();
}
EffectBufferType::BoneTransformData* Vishv::Graphics::EffectBufferData::GetBonetransformData()
{
	VISHVASSERT(mBoneTransformData != nullptr, "[EffectBufferData] trying to get wrong value");
	return mBoneTransformData.get();
}
EffectBufferType::LightData* Vishv::Graphics::EffectBufferData::GetLightData()
{
	VISHVASSERT(mLightsData != nullptr, "[EffectBufferData] trying to set wrong value");
	return mLightsData.get();
}
EffectBufferType::MaterialData* Vishv::Graphics::EffectBufferData::GetMaterialData()
{
	VISHVASSERT(mMaterialData != nullptr, "[EffectBufferData] trying to set wrong value");
	return mMaterialData.get();
}
EffectBufferType::ParticleData* Vishv::Graphics::EffectBufferData::GetParticleData()
{
	VISHVASSERT(mParticleData != nullptr, "[EffectBufferData] trying to set wrong value");
	return mParticleData.get();
}

void Vishv::Graphics::EffectBufferData::Terminate()
{
	if (mFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformData.release();
	if (mFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsData.release();
	if (mFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialData.release();
	if (mFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsData.release();
	if (mFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformData.release();
	if (mFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingData.release();
	if (mFormat & EffectBufferType::EBTYPE_PARTICLE)
		mParticleData.release();
}

