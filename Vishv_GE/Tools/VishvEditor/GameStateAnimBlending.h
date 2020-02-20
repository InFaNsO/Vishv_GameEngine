#pragma once
#include "Vishv/Inc/Vishv.h"
#include "AnimationSet_Gui.h"
#include "Skeleton_Gui.h"



class GameStateAnimBlending : public Vishv::AppState
{
public:
	void Initialize() override;
	void Update(float deltaTime) override;

	void Render() override;

	void RenderDebugUI() override;

	void Terminate() override;
	void RenderSimpleDraw() override;

private:
	void SetAnimations(std::filesystem::path& path);
	void UpdateAnimationPlay(Vishv::Graphics::AnimationPlayInformation& play, float deltaTime);

	int depth = -1;

	float blendTimeTotal = 2.0f;
	float blendTimer = 0.0f;
	bool shouldBlend = false;

	bool shouldPlay = true;

	AnimationMovement currentAnimation = AnimationMovement::IdleStanding1;
	AnimationMovement nextAnimation = AnimationMovement::none;

	std::string loadName;
	std::string loadAnim;

	Vishv::Graphics::Object3D object;
	Vishv::Graphics::AnimationSet animations;

	Vishv::Graphics::Color shallowC = Vishv::Graphics::Colors::OrangeRed;
	Vishv::Graphics::Color deepC = Vishv::Graphics::Colors::LimeGreen;

	std::vector<AnimationMovement> mMovements;

	bool isPLaying = false;
	bool isPause = false;
private:

};


