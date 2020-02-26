#pragma once
#include <Vishv/Inc/Vishv.h>

class EditState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;
	void RenderSimpleDraw();
	void RenderDebugUI() override;
	void Render() override;
	void Terminate() override;
private:
	void RenderScene();
	void PostProcess();

	void DrawMenueBar();
	void SetMainWindow();

	void ShowSceneView();

	void DoUI();
	void MainSceneRender();

	bool shouldStart = false;

	Vishv::GameWorld mWorld;

	std::vector<Vishv::GameObjectHandle> mGO;
};

