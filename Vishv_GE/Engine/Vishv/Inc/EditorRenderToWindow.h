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

		void DoUI();

	private:
		friend class EditorManager;
		friend class GameWorld;

	private:
		uint32_t mWindowHeight = 0;
		uint32_t mWindowWidth = 0;

		Vishv::Graphics::RenderTarget mRenderTarget;
	};
}

