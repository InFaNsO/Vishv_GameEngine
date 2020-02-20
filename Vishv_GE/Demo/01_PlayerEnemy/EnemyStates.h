#pragma once
#include "Vishv/Inc/Vishv.h"

enum class EnemyStates
{
	Empty,
	Wander,
	Chase,
	Attack,
	Dying
};

static std::string ToString(EnemyStates state)
{
	switch (state)
	{
	case EnemyStates::Empty:
		return "Empty";
		break;
	case EnemyStates::Wander:
		return "Wander";
		break;
	case EnemyStates::Chase:
		return "Chase";
		break;
	case EnemyStates::Attack:
		return "Attack";
		break;
	case EnemyStates::Dying:
		return "Dying";
		break;
	default:
		return "none";
		break;
	}
}

