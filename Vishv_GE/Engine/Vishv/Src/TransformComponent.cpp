#include "Precompiled.h"
#include "TransformComponent.h"


META_DERIVED_BEGIN(Vishv::Components::TransformComponent, Vishv::Components::Component)
META_FIELD_BEGIN
		//META_FIELD(mTransform, "Transform")
		META_FIELD(mRotationWorld, "RotationWorld")
		META_FIELD(mRotationLocal, "RotationLocal")
	META_FIELD_END
META_CLASS_END

using namespace Vishv::Components;


void Vishv::Components::TransformComponent::Initialize()
{
}

void Vishv::Components::TransformComponent::Update(float deltaTime)
{
	if (mPrvRotWorld != mRotationWorld)
	{
		mTransform.RotateX(mRotationWorld.x - mPrvRotWorld.x);
		mTransform.RotateY(mRotationWorld.y - mPrvRotWorld.y);
		mTransform.RotateZ(mRotationWorld.z - mPrvRotWorld.z);
		mPrvRotWorld = mRotationWorld;
	}
	if (mPrvRotLocal != mRotationLocal)
	{
		mTransform.RotateRight(mRotationLocal.x - mPrvRotLocal.x);
		mTransform.RotateUp(mRotationLocal.y - mPrvRotLocal.y);
		mTransform.RotateForward(mRotationLocal.z - mPrvRotLocal.z);
		mPrvRotLocal = mRotationLocal;
	}
}

void Vishv::Components::TransformComponent::DebugUI()
{
	if (!ImGui::CollapsingHeader("Transform"))
		return;

	ImGui::DragFloat3("Position", &mTransform.mPosition.x);
	ImGui::DragFloat3("Rotation", &mRotationWorld.x);
}

void Vishv::Components::TransformComponent::SimpleDraw()
{
	Vishv::Graphics::SimpleDraw::AddLine(mTransform.Position(), mTransform.Position() + mTransform.Forward() * 500.0f, Vishv::Graphics::Colors::White);
}

void Vishv::Components::TransformComponent::Render()
{
}


void Vishv::Components::TransformComponent::Terminate()
{
}

