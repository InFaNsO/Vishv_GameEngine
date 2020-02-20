#ifndef INCLUDED_VISHV_AI_PERCEPTION_WORLD
#define INCLUDED_VISHV_AI_PERCEPTION_WORLD

namespace Vishv::AI
{
	//struct Agent;
	template <class AgentType>
	class World
	{
	public:
		using Obstacle = Vishv::Math::Shapes::Capsule;
		using Wall = Vishv::Math::Shapes::Cuboid;

		typedef std::vector<Obstacle> Obstacles;
		typedef std::vector<Wall> Walls;

		void Register(AgentType* agent) { mAgents.push_back(agent); }
		void Register(Obstacle& obstacle) { mObstacles.push_back(obstacle); }
		void Register(Wall& wall) { mWalls.push_back(wall); }
		void RegisterPlayer(AgentType* agent) { mPlayers.push_back(agent); }

		std::vector<AgentType*>& GetAgents() { return mAgents; }
		Obstacle& GetObstacle(uint32_t index) { return mObstacles[index]; }
		Wall& GetWall(uint32_t index) { return mWalls[index]; }

		AgentType & GetAgent(uint32_t index)
		{
			VISHVASSERT(index < mAgents.size(), "[AI::World] Index out of range for the enemies.");
			return *mAgents[index];
		}


		//need to add collision in physics then make it
	//	bool HasLineOfSight(uint32_t enemy, uint32_t player, bool isPlayer = true);
	//	bool HasLineOfSight(uint32_t enemy, uint32_t player, Obstacles& obstacles, bool isPlayer = true);
	//	bool HasLineOfSight(uint32_t enemy, uint32_t player, Walls& walls, bool isPlayer = true);
	//	bool HasLineOfSight(uint32_t enemy, uint32_t player, Obstacles & obstacles, Walls & walls, bool isPlayer = true);

		const Obstacles& GetObstacles()const { return mObstacles; }
		const Walls& GetWalls()const { return mWalls; }

		Obstacles& GetObstacles(){ return mObstacles; }
		Walls& GetWalls(){ return mWalls; }

		AgentType* GetPlayer() { return mPlayers[0]; }

	private:
		std::vector<AgentType*> mPlayers;
		std::vector<AgentType*> mAgents;
		Obstacles mObstacles;
		Walls mWalls;
	};
}


#endif // !INCLUDED_VISHV_AI_PERCEPTION_WORLD


#pragma once
