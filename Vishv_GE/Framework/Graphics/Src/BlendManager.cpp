#include "Precompiled.h"
#include "BlendManager.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	std::unique_ptr<BlendManager> sBlendManager = nullptr;
}

const std::string Blend::Opaque = "Opaque";
const std::string Blend::AlphaBlend = "AlphaBlend";
const std::string Blend::AlphaPremultiplied = "AlphaPremultiplied";
const std::string Blend::Additive = "Additive";

void Vishv::Graphics::BlendManager::StaticInitialize()
{
	VISHVASSERT(sBlendManager == nullptr, "[Vishv::Graphics::TextureManager::StaticInitialize] Already static Initialized");

	sBlendManager = std::make_unique<BlendManager>();
	sBlendManager.get()->Initialize();
}

void Vishv::Graphics::BlendManager::StaticTerminate()
{
	if (sBlendManager != nullptr)
	{
		sBlendManager.get()->Terminate();
		sBlendManager = nullptr;
	}
}

BlendManager * Vishv::Graphics::BlendManager::Get()
{
	return sBlendManager.get();
}

Vishv::Graphics::BlendManager::~BlendManager()
{
}

void Vishv::Graphics::BlendManager::Initialize()
{
	AddState(BlendState::Mode::Opaque);
	AddState(BlendState::Mode::Additive);
	AddState(BlendState::Mode::AlphaBlend);
	AddState(BlendState::Mode::AlphaPremultiplied);
}

bool Vishv::Graphics::BlendManager::AddState(std::string name)
{
	return AddState(StringToEnum(name));
}

bool Vishv::Graphics::BlendManager::AddState(BlendState::Mode mode)
{
	auto[iter, success] = mInventory.try_emplace(mode, nullptr);
	if (success)
	{
		auto blend = std::make_unique<BlendState>();
		blend->Initialize(mode);
		iter->second = std::move(blend);
	}
	return success;
}

bool Vishv::Graphics::BlendManager::SetState(std::string name)
{
	return SetState(StringToEnum(name));
}

bool Vishv::Graphics::BlendManager::SetState(BlendState::Mode mode)
{
	auto iter = mInventory.find(mode);
	if (iter != mInventory.end())
	{
		BlendState::Clear();
		iter->second->Set();
		return true;
	}
	return false;
}

bool Vishv::Graphics::BlendManager::ClearState(std::string name)
{
	BlendState::Clear();
	return true;
}

bool Vishv::Graphics::BlendManager::ClearState(BlendState::Mode mode)
{
	BlendState::Clear();
	return true;
}

bool Vishv::Graphics::BlendManager::TerminateState(BlendState::Mode mode)
{
	auto iter = mInventory.find(mode);
	if (iter != mInventory.end())
	{
		iter->second->Terminate();
		return true;
	}
	return false;
}

Vishv::Graphics::BlendState::Mode Vishv::Graphics::BlendManager::StringToEnum(std::string name)
{
	if (name == "Opaque")
		return BlendState::Mode::Opaque;
	if (name == "Additive")
		return BlendState::Mode::Additive;
	if (name == "AlphaBlend")
		return BlendState::Mode::AlphaBlend;
	if (name == "AlphaPremultiplied")
		return BlendState::Mode::AlphaPremultiplied;
	return BlendState::Mode::Opaque;
}

void Vishv::Graphics::BlendManager::Terminate()
{
	ClearState("Opaque");
	ClearState("Additive");
	ClearState("AlphaBlend");
	ClearState("AlphaPremultiplied");

	TerminateState(BlendState::Mode::Opaque);
	TerminateState(BlendState::Mode::Additive);
	TerminateState(BlendState::Mode::AlphaBlend);
	TerminateState(BlendState::Mode::AlphaPremultiplied);
}
