#include "Precompiled.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "GameObject.h"

META_CLASS_BEGIN(Vishv::Components::ColliderComponent)
	META_FIELD_BEGIN
		META_FIELD(mOffset, "Offset")
		//META_FIELD(mExtent, "Extent")
	META_FIELD_END
META_CLASS_END


void Vishv::Components::ColliderComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	pworld = &GetOwner().GetWorld().GetPhysicsWorld();
	mSphereCollider.mSphere.mTransform.mPosition = mTransformComponent->Position();
}

void Vishv::Components::ColliderComponent::Update(float deltaTime)
{
	//this needs to be fixed
	mSphereCollider.mSphere.mTransform.mPosition = mTransformComponent->Position() + mOffset;
}

void Vishv::Components::ColliderComponent::DebugUI()
{
	if (!ImGui::CollapsingHeader("Collider"))
		return;

	ImGui::DragFloat3("Offset", &mOffset.x);
	ImGui::DragFloat("Extend", &mSphereCollider.mSphere.mRadius);
}

void Vishv::Components::ColliderComponent::SimpleDraw()
{
	Vishv::Graphics::SimpleDraw::AddSphere(mSphereCollider.mSphere.mTransform.Position(), mSphereCollider.mSphere.mRadius, Vishv::Graphics::Colors::Firebrick, 6, 6);
}

void Vishv::Components::ColliderComponent::SetTag(int tag)
{
	mSphereCollider.mTag = tag;
}

int Vishv::Components::ColliderComponent::GetTag()
{
	return mSphereCollider.mTag;
}

bool Vishv::Components::ColliderComponent::IsColliding(int tag)
{
	return pworld->IsColliding(tag, mSphereCollider).has_value();
}

std::vector<Vishv::GameObject*> Vishv::Components::ColliderComponent::GetCollisions(int tag)
{
	auto collisons = pworld->IsColliding(tag, mSphereCollider);
	if(!collisons.has_value())
		return std::vector<Vishv::GameObject*>();

	std::vector<Vishv::GameObject*> comps;
	comps.resize(collisons.value().size());

	for (auto& obj : collisons.value())
	{
		comps.emplace_back(GetOwner().GetWorld().GetGameObject(obj->objectID));
	}

	return std::move(comps);
}

