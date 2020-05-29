#pragma once
#include "Component.h"

namespace Vishv
{
	class PostProcessService;
	//namespace Editor
	//{
	//	class RenderToWindow;
	//}
}

namespace Vishv::Components
{
	class Model3D;

	class PostProcessor : public Component
	{
	public:
		META_CLASS_DECLARE

		void Initialize() override;
		void DebugUI() override;
		void Update() override;
		//void Render() override;

		void AddEffect(Graphics::EffectType effect);
		Graphics::EffectType GetCurrentEffect();

		//Editor::RenderToWindow* GetFinalRenderTarget();

	private:
		void CustomRender(Graphics::EffectType effect);
		void UpdateCellShader(int index);
		void UICellShader(int index);


	private:
		void RenderSkinning();

	private:
		friend class PostProcessService;

		int MyEffects = 0;

		Model3D* myModel = nullptr;
		PostProcessService* PPservice = nullptr;

		std::vector<Graphics::EffectType> myEffects;
		std::vector<Graphics::EffectBufferType::OptionsData> mEffectOptions;
		//std::vector<std::unique_ptr<Editor::RenderToWindow>> myEffectsRT;

		Graphics::MeshBuffer mScreenMeshBuffer;
	};
}
