#include "HealthComponent.h"

META_DERIVED_BEGIN(HealthComponent, Vishv::Components::Component)
	META_FIELD_BEGIN
		META_FIELD(mHealth, "Health")
	META_FIELD_END
META_CLASS_END

void HealthComponent::DebugUI()
{
	if (ImGui::CollapsingHeader("HealthComponent"))
		ImGui::DragFloat("Health", &mHealth, 1.0f, 0.0f);
}
void HealthComponent::SetHealth(float hp)
{
	mHealth = hp;
}


void HealthComponent::TakeDamage(float damage)
{
	mHealth -= damage;
}

bool HealthComponent::IsAlive()
{
	return mHealth > 0.0f;
}


