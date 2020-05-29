#pragma once
#include "Service.h"

namespace Vishv
{
	namespace Editor
	{
		class RenderToWindow;
	}
	namespace Components
	{
		class PostProcessor;
	}

	class Lighting;

	class PostProcessService : public Service
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void RegisterProcessor(Components::PostProcessor& pp);

		void Render() override;
		Graphics::EffectType GetCurrentEffect() { return mCurrentEffect; }

	private:
		std::vector<Components::PostProcessor*>  myPostProcessor;

		Lighting* mLighting = nullptr;
		Service* mSkyBox = nullptr;
		Service* mSimpleDraw = nullptr;

		Graphics::EffectType mCurrentEffect = Graphics::EffectType::Count;

		//std::vector<std::unique_ptr<Editor::RenderToWindow>> myEffectsRT;
		std::unique_ptr<Editor::RenderToWindow> mMainRT = nullptr;
		Graphics::MeshBuffer mScreenMeshBuffer;
	};
}

