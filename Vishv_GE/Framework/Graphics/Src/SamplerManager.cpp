#include "Precompiled.h"
#include "SamplerManager.h"

namespace
{
	std::unique_ptr<Vishv::Graphics::SamplerManager> sInstance = nullptr;
}

void Vishv::Graphics::SamplerManager::StaticInitialize()
{
	VISHVASSERT(sInstance == nullptr, "[SamplerManager] already Initialized");
	sInstance = std::make_unique<SamplerManager>();
	sInstance->Initialize();
}

void Vishv::Graphics::SamplerManager::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

Vishv::Graphics::SamplerManager * Vishv::Graphics::SamplerManager::Get()
{
	VISHVASSERT(sInstance != nullptr, "[SamplerManager] not Initialized");

	return sInstance.get();
}

void Vishv::Graphics::SamplerManager::Initialize()
{
	AddSampler("PointClamp", Sampler::Filter::Point, Sampler::AddressMode::Clamp);
	AddSampler("PointWrap", Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	AddSampler("LinearClamp", Sampler::Filter::Linear, Sampler::AddressMode::Clamp);
	AddSampler("LinearWrap", Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	AddSampler("AnistropicClamp", Sampler::Filter::Anistropic, Sampler::AddressMode::Clamp);
	AddSampler("AnistropicWrap", Sampler::Filter::Anistropic, Sampler::AddressMode::Wrap);
}

bool Vishv::Graphics::SamplerManager::AddSampler(std::string name, Sampler::Filter filter, Sampler::AddressMode adderessMode)
{
	return AddSampler(StringToEnum(name), filter, adderessMode);
}

bool Vishv::Graphics::SamplerManager::AddSampler(Vishv::Graphics::SamplerManager::SamplerType name, Sampler::Filter filter, Sampler::AddressMode adderessMode)
{
	auto[iter, success] = mInventory.try_emplace(name, nullptr);
	if (success)
	{
		auto sampler = std::make_unique<Sampler>();
		sampler->Initialize(filter, adderessMode);
		iter->second = std::move(sampler);
	}
	return success;
}

Vishv::Graphics::SamplerManager::SamplerType Vishv::Graphics::SamplerManager::StringToEnum(std::string name)
{
	if (name == "PointClamp")
		return SamplerType::PointClamp;
	if (name == "PointWrap")
		return SamplerType::PointWrap;
	if (name == "LinearClamp")
		return SamplerType::LinearClamp;
	if (name == "LinearWrap")
		return SamplerType::LinearWrap;
	if (name == "AnistropicClamp")
		return SamplerType::AnistropicClamp;
	if (name == "AnistropicWrap")
		return SamplerType::PointClamp;

	return SamplerType::PointWrap;
}

Vishv::Graphics::Sampler * Vishv::Graphics::SamplerManager::GetSampler(std::string name)
{
	return GetSampler(StringToEnum(name));
}

Vishv::Graphics::Sampler * Vishv::Graphics::SamplerManager::GetSampler(Vishv::Graphics::SamplerManager::SamplerType name)
{
	auto iter = mInventory.find(name);
	return iter != mInventory.end() ? iter->second.get() : nullptr;
}

void Vishv::Graphics::SamplerManager::Terminate()
{
	for(auto&[key, value] : mInventory)
		value->Terminate();
}

Vishv::Graphics::SamplerManager::~SamplerManager()
{
}