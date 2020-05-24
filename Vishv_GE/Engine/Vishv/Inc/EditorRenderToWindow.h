#pragma once

namespace Vishv
{
	class EditorManager;
	class GameWorld;
}

namespace Vishv::Editor
{
	class RenderToWindow
	{
	public:
		void Initialize();
		void Terminate();
		void Resize();
		void Resize(Math::Vector2 dimension);

		void DoUI();

		void BeginRender() { mRenderTarget.BeginRender(); }
		void EndRender() { mRenderTarget.EndRender(); }

		void BindTexture(uint32_t i = 0) { mRenderTarget.BindPS(i); }

	private:
		friend class EditorManager;
		friend class GameWorld;

	private:
		uint32_t mWindowHeight = 0;
		uint32_t mWindowWidth = 0;

		Vishv::Graphics::RenderTarget mRenderTarget;
	};
}

