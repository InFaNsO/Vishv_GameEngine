#ifndef INCLUDED_VISHV_AI_WROLD_SERVICE_H
#define INCLUDED_VISHV_AI_WROLD_SERVICE_H
#pragma

#include "Service.h"

namespace Vishv
{
	namespace Components
	{
		class AIAgent;
		class OBBCollider;
		class CapsuleCollider;
	}

	class GameObject;

	class AIWorld : public Service
	{
	public:
		META_CLASS_DECLARE

		using Obstacle = Components::CapsuleCollider;
		using Wall = Components::OBBCollider;

		void Initialize() override;
		void Terminate() override;

		void Update() override;
		void Render() override;
		void DebugUI() override;

		void Register(GameObject& object);
		void RegisterPlayer(GameObject& object);

		std::vector<Components::AIAgent*> GetAgents();


	private:
		std::vector<GameObject*> mPlayers;
		std::vector<Components::AIAgent*> mAgents;
		std::vector<Obstacle*> mObstacles;
		std::vector<Wall*> mWalls;

	};
}



#endif // !INCLUDED_VISHV_AI_WROLD_SERVICE_H



