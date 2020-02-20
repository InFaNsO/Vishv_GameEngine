#include "Precompiled.h"
#include "EffectsManager.h"


namespace
{
	std::unique_ptr<Vishv::Graphics::EffectsManager> sInstance = nullptr;
}

using namespace Vishv::Graphics;

void Vishv::Graphics::EffectsManager::StaticInitialize()
{
	VISHVASSERT(sInstance == nullptr, "[SamplerManager] already Initialized");
	sInstance = std::make_unique<EffectsManager>();
	sInstance->Initialize();
}

void Vishv::Graphics::EffectsManager::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

Vishv::Graphics::EffectsManager * Vishv::Graphics::EffectsManager::Get()
{
	VISHVASSERT(sInstance != nullptr, "[SamplerManager] not Initialized");

	return sInstance.get();
}

void Vishv::Graphics::EffectsManager::Initialize()
{

}

void Vishv::Graphics::EffectsManager::Terminate()
{
	for (auto iter = mInventory.begin(); iter != mInventory.end(); ++iter)
	{
		iter->second->Terminate();
		iter->second.release();
	}
	mInventory.clear();
}

bool Vishv::Graphics::EffectsManager::AddEffect(EffectType type)
{
	auto path = GetPath(type);
	if(path == "wrong input")
		return false;

	//auto hash = std::filesystem::hash_value(fileName);

	auto[iter, success] = mInventory.insert({ type, nullptr });
	if (success)
	{
		iter->second = std::make_unique<Effect>();
		iter->second->Initialize(GetPath(type), GetShaderType(type), GetBufferType(type), GetVertexType(type));
	}

	return success;
}

bool Vishv::Graphics::EffectsManager::BindBuffer(EffectType type)
{
	auto iter = mInventory.find(type);

	if (iter == mInventory.end())
		return false;

	iter->second->mConstantBuffer.Bind();
	return true;
}

bool Vishv::Graphics::EffectsManager::BindEffect(EffectType type)
{
	auto iter = mInventory.find(type);

	if (iter == mInventory.end())
		return false;

	iter->second->BindEffects();
	return true;
}

uint32_t Vishv::Graphics::EffectsManager::GetBufferFormat(EffectType type)
{
	auto iter = mInventory.find(type);

	if (iter == mInventory.end())
		return 0;

	return iter->second->mBufferData.GetFormat();
}

EffectBufferData * Vishv::Graphics::EffectsManager::GetBufferData(EffectType type)
{
	auto iter = mInventory.find(type);

	if (iter == mInventory.end())
		return nullptr;

	return &iter->second->mBufferData;
}

void Vishv::Graphics::EffectsManager::Set(EffectType type)
{
	auto iter = mInventory.find(type);

	if (iter == mInventory.end())
		return;

	iter->second->mConstantBuffer.Set(iter->second->mBufferData);
}

std::string Vishv::Graphics::EffectsManager::GetPath(EffectType type)
{
	std::string path = "../../Assets/Shaders/";

	switch (type)
	{
	case Vishv::Graphics::EffectType::Blur:
		return std::move(path + "Blur.fx");
		break;
	case Vishv::Graphics::EffectType::DoLighting:
		return std::move(path + "DoLighting.fx");
		break;
	case Vishv::Graphics::EffectType::DoNothing:
		return std::move(path + "DoNothing.fx");
		break;
	case Vishv::Graphics::EffectType::DoSomething:
		return std::move(path + "DoSomething.fx");
		break;
	case Vishv::Graphics::EffectType::Merge:
		return std::move(path + "Merge.fx");
		break;
	case Vishv::Graphics::EffectType::Particle:
		return std::move(path + "Particle.fx");
		break;
	case Vishv::Graphics::EffectType::PostProcessing:
		return std::move(path + "PostProcessing.fx");
		break;
	case Vishv::Graphics::EffectType::SimpleDraw:
		return std::move(path + "SimpleDrawShader.fx");
		break;
	case Vishv::Graphics::EffectType::Skinning:
		return std::move(path + "Skining.fx");
		break;
	case Vishv::Graphics::EffectType::Standard:
		return std::move(path + "Standard.fx");
		break;
	case Vishv::Graphics::EffectType::Texturing:
		return std::move(path + "Texturing.fx");
		break;
	case Vishv::Graphics::EffectType::Mixamo:
		return std::move(path + "Mixamo.fx");
		break;
	default:
		return "wrong input";
		break;
	}
}

uint32_t Vishv::Graphics::EffectsManager::GetBufferType(EffectType type)
{
	switch (type)
	{
	case Vishv::Graphics::EffectType::Blur:
		return 0;
		break;
	case Vishv::Graphics::EffectType::DoLighting:
		return EffectBufferType::EBTYPE_TRANSFORM | EffectBufferType::EBTYPE_LIGHT | EffectBufferType::EBTYPE_MATERIAL;
		break;
	case Vishv::Graphics::EffectType::DoNothing:
		return 0;
		break;
	case Vishv::Graphics::EffectType::DoSomething:
		return 0;
		break;
	case Vishv::Graphics::EffectType::Merge:
		return 0;
		break;
	case Vishv::Graphics::EffectType::Particle:
		return EffectBufferType::EBTYPE_PARTICLE;
		break;
	case Vishv::Graphics::EffectType::PostProcessing:
		return 0;
		break;
	case Vishv::Graphics::EffectType::SimpleDraw:
		return EffectBufferType::EBTYPE_TEXTURING;
		break;
	case Vishv::Graphics::EffectType::Skinning:
		return EffectBufferType::EBTYPE_TRANSFORM | EffectBufferType::EBTYPE_LIGHT | EffectBufferType::EBTYPE_MATERIAL | EffectBufferType::EBTYPE_OPTIONS | EffectBufferType::EBTYPE_BONE;
		break;
	case Vishv::Graphics::EffectType::Standard:
		return EffectBufferType::EBTYPE_TRANSFORM | EffectBufferType::EBTYPE_LIGHT | EffectBufferType::EBTYPE_MATERIAL | EffectBufferType::EBTYPE_OPTIONS;
		break;
	case Vishv::Graphics::EffectType::Texturing:
		return EffectBufferType::EBTYPE_TEXTURING;
		break;
	case Vishv::Graphics::EffectType::Mixamo:
		return EffectBufferType::EBTYPE_TRANSFORM | EffectBufferType::EBTYPE_LIGHT | EffectBufferType::EBTYPE_MATERIAL | EffectBufferType::EBTYPE_OPTIONS | EffectBufferType::EBTYPE_BONE;
		break;
	default:
		return 0;
		break;
	}
}

uint32_t Vishv::Graphics::EffectsManager::GetShaderType(EffectType type)
{
	uint32_t val = ShaderType::EF_PIXEL | ShaderType::EF_VERTEX;

	if (type == EffectType::Particle)
		val |= ShaderType::EF_GEOMETRY;

	return val;
}

uint32_t Vishv::Graphics::EffectsManager::GetVertexType(EffectType type)
{
	switch (type)
	{
	case Vishv::Graphics::EffectType::Blur:
		return VertexPX::Format;
		break;
	case Vishv::Graphics::EffectType::DoLighting:
		return VertexPN::Format;
		break;
	case Vishv::Graphics::EffectType::DoNothing:
		return 0;
		break;
	case Vishv::Graphics::EffectType::DoSomething:
		return VertexPC::Format;
		break;
	case Vishv::Graphics::EffectType::Merge:
		return VertexPX::Format;
		break;
	case Vishv::Graphics::EffectType::Particle:
		return VertexPNC::Format;
		break;
	case Vishv::Graphics::EffectType::PostProcessing:
		return VertexPX::Format;
		break;
	case Vishv::Graphics::EffectType::SimpleDraw:
		return VertexPC::Format;
		break;
	case Vishv::Graphics::EffectType::Skinning:
		return BoneVertex::Format;
		break;
	case Vishv::Graphics::EffectType::Standard:
		return Vertex::Format;
		break;
	case Vishv::Graphics::EffectType::Texturing:
		return VertexPX::Format;
		break;
	case Vishv::Graphics::EffectType::Mixamo:
		return BoneVertex::Format;
		break;
	default:
		return 0;
		break;
	}
}


Vishv::Graphics::EffectsManager::~EffectsManager()
{
	VISHVASSERT(mInventory.empty(), "[EffectsManager] Not terminated");
}