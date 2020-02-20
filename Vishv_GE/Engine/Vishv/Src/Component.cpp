#include "Precompiled.h"
#include "Component.h"

#include "GameObject.h"

META_CLASS_BEGIN(Vishv::Components::Component)
	META_NO_FIELD
META_CLASS_END

Vishv::GameObject & Vishv::Components::Component::GetOwner()
{
	return *mOwner;
}

const Vishv::GameObject & Vishv::Components::Component::GetOwner() const
{
	return *mOwner;
}