#ifndef INCLUDED_VISHV_COMPONENTS_AIPATHFINDING_H
#define INCLUDED_VISHV_COMPONENTS_AIPATHFINDING_H

#include "Component.h"

namespace Vishv::Components
{
	class AIPathFinding : public Component
	{
	public:
		META_CLASS_DECLARE

			void Initialize() override;
		void Terminate() override;

		void Update() override;
		void SimpleDraw() override;
		void DebugUI() override;

		Math::Vector3 GetRandomNodePos();
		uint32_t GetNodeID(const Math::Vector3& pos);
		const std::vector<Math::Vector3>& RunAStar(const Math::Vector3& start, const Math::Vector3& end);

	private:
		void Save();
		void Load(std::filesystem::path p);

		AI::Graph mGraph;
		AI::GraphSearch mGraphSearch;

		AI::Node* mCurrentNode = nullptr;

		bool mShowAll = false;

		float radius = 2.0f;

		bool useGrid = true;

		//2d grid setup
		Math::Vector3 mStartPos = {0.0f, 10.0f, 0.0f};
		int graphRow = 1;
		int graphCol = 1;
		float rowThickness = 10.0f;
		float colThickness = 10.0f;
	};
}

#endif // !INCLUDED_VISHV_COMPONENTS_AIPATHFINDING_H

