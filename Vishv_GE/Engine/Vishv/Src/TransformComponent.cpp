#include "Precompiled.h"
#include "TransformComponent.h"

using namespace Vishv::Components;


META_DERIVED_BEGIN(TransformComponent, Component)
	META_FIELD_BEGIN
		//META_FIELD(pos, "Position")
		//META_FIELD(mQuaternion, "Orientation")
		//META_FIELD(scale, "Scale")
	META_FIELD_END
META_CLASS_END



void Vishv::Components::TransformComponent::Initialize()
{
	VISHVASSERT(true, "Entered the transform iniialize");
}


void Vishv::Components::TransformComponent::Update()	//Disabled for now
{
	return;
	if (mQuaternion != mTransform.Rotation())
	{
		mTransform.SetRotation(mQuaternion);
	}

	if (changePos)
		pos = mTransform.Position();
	else if (pos != mTransform.Position())
		mTransform.mPosition = pos;

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

void Vishv::Components::TransformComponent::SimpleDraw()
{
	Vishv::Graphics::SimpleDraw::AddLine(mTransform.Position(), mTransform.Position() + mTransform.Forward() * 500.0f, Vishv::Graphics::Colors::White);
}

void Vishv::Components::TransformComponent::DebugUI()
{
	using namespace Vishv::Math;

	ImGui::DragFloat3("Position", &mTransform.mPosition.x, 0.1f);
	if (ImGui::DragFloat3("Rotation", &mRotation.x))
	{
		mTransform.SetRotation(Quaternion(XAxis, mRotation.x * Constans::DegToRad) * 
			Quaternion(YAxis, mRotation.y * Constans::DegToRad) *
			Quaternion(ZAxis, mRotation.z * Constans::DegToRad));
	}
	if (mRotation == Vector3())
	{
		mTransform.SetRotation(mQuaternion.CreateIdentity());
	}
	ImGui::DragFloat3("Scale", &mTransform.mScale.x, 0.1f);
}

void Vishv::Components::TransformComponent::SetTransformation(const Math::Matrix4& mat)
{
	mTransform.SetTransformation(mat);
}
