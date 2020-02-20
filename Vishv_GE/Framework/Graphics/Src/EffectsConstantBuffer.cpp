#include "Precompiled.h"
#include "EffectsConstantBuffer.h"


void Vishv::Graphics::EffectsConstantBuffer::Intialize(uint32_t dataFormat, uint32_t shaderFormat)
{
	mDataFormat = dataFormat;

	if (mDataFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::TransformData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::LightData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::MaterialData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::OptionsData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::BoneTransformData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::TextureingData>>();
	if (mDataFormat & EffectBufferType::EBTYPE_PARTICLE)
		mParticleBuffer = std::make_unique<TypedConstantBuffer<EffectBufferType::ParticleData>>();

	Init();

	mFormat = shaderFormat;
}

void Vishv::Graphics::EffectsConstantBuffer::Init()
{
	if (mDataFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingBuffer.get()->Initialize();
	if (mDataFormat & EffectBufferType::EBTYPE_PARTICLE) {}
		mParticleBuffer.get()->Initialize();
}

void Vishv::Graphics::EffectsConstantBuffer::Set(EffectBufferData & data)
{
	if (mDataFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformBuffer.get()->Set(*data.GetTransform());
	if (mDataFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsBuffer.get()->Set(*data.GetLightData());
	if (mDataFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialBuffer.get()->Set(*data.GetMaterialData());
	if (mDataFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsBuffer.get()->Set(*data.GetOptionsData());
	if (mDataFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformBuffer.get()->Set(*data.GetBonetransformData());
	if (mDataFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingBuffer.get()->Set(*data.GetTextureing());
	if (mDataFormat & EffectBufferType::EBTYPE_PARTICLE)
		mParticleBuffer.get()->Set(*data.GetParticleData());
}

void Vishv::Graphics::EffectsConstantBuffer::Bind()
{
	int count = 0;
	if (mTextureingBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mTextureingBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mTextureingBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mTextureingBuffer->BindGS(count);
		++count;
	}
	if (mParticleBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mParticleBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mParticleBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mParticleBuffer->BindGS(count);
		++count;
	}
	if (mTransformBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mTransformBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mTransformBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mTransformBuffer->BindGS(count);
		++count;
	}
	if (mLightsBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mLightsBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mLightsBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mLightsBuffer->BindGS(count);
		++count;
	}
	if (mMaterialBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mMaterialBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mMaterialBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mMaterialBuffer->BindGS(count);
		++count;
	}
	if (mOptionsBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mOptionsBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mOptionsBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mOptionsBuffer->BindGS(count);
		++count;
	}
	if (mBoneTransformBuffer != nullptr)
	{
		if (mFormat & ShaderType::EF_VERTEX)
			mBoneTransformBuffer->BindVS(count);
		if (mFormat & ShaderType::EF_PIXEL)
			mBoneTransformBuffer->BindPS(count);
		if (mFormat & ShaderType::EF_GEOMETRY)
			mBoneTransformBuffer->BindGS(count);
		++count;
	}
}

void Vishv::Graphics::EffectsConstantBuffer::Terminate()
{
	if (mDataFormat & EffectBufferType::EBTYPE_TRANSFORM)
		mTransformBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_LIGHT)
		mLightsBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_MATERIAL)
		mMaterialBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_OPTIONS)
		mOptionsBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_BONE)
		mBoneTransformBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_TEXTURING)
		mTextureingBuffer.get()->Terminate();
	if (mDataFormat & EffectBufferType::EBTYPE_PARTICLE)
		mParticleBuffer.get()->Terminate();
	mDataFormat = 0;
}

