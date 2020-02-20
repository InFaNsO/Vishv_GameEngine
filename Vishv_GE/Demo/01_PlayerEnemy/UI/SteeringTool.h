#pragma once
#include "Vishv/Inc/Vishv.h"


namespace Vishv::UI
{
	class SteeringTool
	{
	public:
		void Initialize(Vishv::AI::Agent& agent, Vishv::AI::SteeringModule& sm);

		void DrawUI();
		void SimpleDraw();

	private:
		void ChangeBehaviour();

		void Seek();
		void Arrive();
		void Wander();


		int mCurrentBehaviour = (int)AI::SteeringType::base;
		Vishv::AI::Agent* a;
		Vishv::AI::SteeringModule* mModule;
	
		Math::Vector3 mTarget = {5.0f,5.0f,5.0f};

		bool isSeek = false;
		bool isWander = false;
		bool isArrive = false;
		bool isEvade = false;
		bool isFlee = false;
		bool isFlocking = false;
		bool isOA = false;
		bool isPursuit = false;

	};
}
