#include "WeaponComponent.h"

META_DERIVED_BEGIN(WeaponComponent, Vishv::Components::Component)
	META_FIELD_BEGIN
		META_FIELD(mDamage, "Damage")
	META_FIELD_END
META_CLASS_END


void WeaponComponent::DebugUI()
{
	if (ImGui::CollapsingHeader("WeaponComponent"))
	{
		ImGui::DragFloat("Damage", &mDamage, 0.1f);
	}
}

void WeaponComponent::Use(HealthComponent & hc)
{
	hc.TakeDamage(mDamage);
}

