#pragma once
#include "Vishv/Inc/Vishv.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"


namespace Demo {
	static void MetaRegistration()
	{
		META_REGISTER(HealthComponent);
		META_REGISTER(WeaponComponent);
	}
}
