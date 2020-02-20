#pragma once
#include <Vishv/Inc/Vishv.h>


class MainState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void Render() override;

	void RenderDebugUI() override;

	void Terminate() override;
	void RenderSimpleDraw() override;

private:

	std::vector<Vishv::Graphics::Object3D> mEnemiesObject;
	std::vector<Vishv::AI::Agent> mEnemiesAI;

	bool drawGraph = false;
	bool drawCL = true;

	int graphRow = 10;
	int graphCol = 10;
	float rowThick = 10.0f;
	float colThick = 10.0f;

	int startRow = 5;
	int startCol = 6;

	int endRow = 0;
	int endCol = 0;

	Vishv::Math::Vector3 startPosition;

	bool hasPath = false;

	Vishv::AI::Graph mGraph;
	Vishv::AI::World mGameWorld;
	Vishv::AI::GraphSearch mGraphSearch;

	int searchType = 0;

	std::vector<Vishv::Math::Vector3>* path;
};

