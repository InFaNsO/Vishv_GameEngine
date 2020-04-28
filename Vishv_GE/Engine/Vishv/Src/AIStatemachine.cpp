#include "Precompiled.h"
#include "AIStateMachine.h"
#include "GameObject.h"

using namespace Vishv::Components;

META_DERIVED_BEGIN(AIStateMachine, Component)
	META_NO_FIELD	//need to fix the MEta template
META_CLASS_END

void Vishv::Components::AIStateMachine::Initialize()
{
	mStateMachine = std::make_unique<AI::FSM::StateMachine<GameObject>>(GetOwner());
}

void Vishv::Components::AIStateMachine::Update()
{
	if (!mStateMachine->HasStates())
		return;

	mStateMachine->Update(Core::Time::Get()->DeltaTime());
}

void Vishv::Components::AIStateMachine::SimpleDraw()
{
	if (!mStateMachine->HasStates())
		return;

	mStateMachine->SimpleDraw();
}

void Vishv::Components::AIStateMachine::DebugUI()
{
	if (!mStateMachine->HasStates())
		return;
	mStateMachine->DebugUI();
}

void Vishv::Components::AIStateMachine::Terminate()
{
	if (!mStateMachine->HasStates())
		return;

	mStateMachine->Purge();
}

