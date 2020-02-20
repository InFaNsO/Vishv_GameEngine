#pragma once
#include "Vishv/Inc/Vishv.h"
#include "HealthComponent.h"

class WeaponComponent : public Vishv::Components::Component
{
public:
	META_CLASS_DECLARE

	void Initialize() override {}
	void Update(float deltaTime) override {}
	void DebugUI() override;
	void SimpleDraw() override {}
	void Render() override {}
	void Terminate() override {}


	void Use(HealthComponent& hc);

private:
	float mDamage = 10.0f;
};
