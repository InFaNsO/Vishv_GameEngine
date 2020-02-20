#include "Precompiled.h"
#include "RasterizerStateManager.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	std::unique_ptr<RasterizerManager> sRasterizerManager = nullptr;
}

void Vishv::Graphics::RasterizerManager::StaticInitialize()
{
	VISHVASSERT(sRasterizerManager == nullptr, "[Vishv::Graphics::TextureManager::StaticInitialize] Already static Initialized");

	sRasterizerManager = std::make_unique<RasterizerManager>();
	sRasterizerManager->Initialize();
	sRasterizerManager->SetState("BackSolid");
}

void Vishv::Graphics::RasterizerManager::StaticTerminate()
{
	if (sRasterizerManager != nullptr)
	{
		sRasterizerManager->Terminate();
		sRasterizerManager = nullptr;
	}
}

RasterizerManager * Vishv::Graphics::RasterizerManager::Get()
{
	return sRasterizerManager.get();
}

void Vishv::Graphics::RasterizerManager::Initialize()
{
	AddState("FrontWire", RasterizerState::CullMode::Front, RasterizerState::FillMode::Wireframe);
	AddState("BackWire", RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);
	AddState("NoneWire", RasterizerState::CullMode::None, RasterizerState::FillMode::Wireframe);
	AddState("FrontSolid", RasterizerState::CullMode::Front, RasterizerState::FillMode::Solid);
	AddState("BackSolid", RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	AddState("NoneSolid", RasterizerState::CullMode::None, RasterizerState::FillMode::Solid);
}

bool Vishv::Graphics::RasterizerManager::AddState(std::string name, RasterizerState::CullMode cMode, RasterizerState::FillMode fMode)
{
	auto[iter, success] = mStates.try_emplace(name, nullptr);
	if (success)
	{
		auto state = std::make_unique<RasterizerState>();
		state->Initialize(cMode, fMode);
		iter->second = std::move(state);
	}
	return success;
}

bool Vishv::Graphics::RasterizerManager::SetState(std::string name)
{
	auto iter = mStates.find(name);
	if (iter != mStates.end())
	{
		mCurrentState = std::move(name);
		iter->second->Set();
		return true;
	}
	return false;
}

bool Vishv::Graphics::RasterizerManager::ClearState(std::string name)
{
	auto iter = mStates.find(name);
	if (iter != mStates.end())
	{
		mCurrentState = "";
		iter->second->Clear();
		return true;
	}
	return false;
}

bool Vishv::Graphics::RasterizerManager::ChangeState(std::string name)
{
	ClearState(mCurrentState);
	return SetState(name);
}

void Vishv::Graphics::RasterizerManager::Terminate()
{
	ClearState(mCurrentState);

	TerminateState("FrontWire");
	TerminateState("BackWire");
	TerminateState("NoneWire");
	TerminateState("FrontSolid");
	TerminateState("BackSolid");
	TerminateState("NoneSolid");
}

bool Vishv::Graphics::RasterizerManager::TerminateState(std::string name)
{
	auto iter = mStates.find(name);
	if (iter != mStates.end())
	{
		iter->second->Terminate();
		return true;
	}
	return false;
}

