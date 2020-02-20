#pragma once
#include <Vishv/Inc/Vishv.h>


class GameState : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void Render() override;

	void BoneSetting(int boneId);
	void RenderDebugUI() override;

	void Terminate() override;
	void RenderSimpleDraw() override;

private:
	int GetDepth(Vishv::Graphics::Bone* bone);

	void SetColorBasedOnDepth(Vishv::Graphics::Bone* bone, int currentDepth, int totalDepth);

	int depth = -1;

	std::string loadName;
	std::string loadAnim;

	Vishv::Graphics::Object3D object;
	Vishv::Graphics::AnimationSet animations;

	Vishv::Graphics::Color shallowC = Vishv::Graphics::Colors::OrangeRed;
	Vishv::Graphics::Color deepC = Vishv::Graphics::Colors::LimeGreen;

	bool isPLaying = false;
	bool isPause = false;
private:

};

