#pragma once
#include "Vishv/Inc/Vishv.h"

	class HealthComponent : public  Vishv::Components::Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override {}
		void Update(float deltaTime) override {}
		void DebugUI() override;
		void SimpleDraw() override {}
		void Render() override {}
		void Terminate() override {}

		void SetHealth(float hp);
		void TakeDamage(float damage);
		bool IsAlive();


	private:
		float mHealth = 100.0f;
	};

