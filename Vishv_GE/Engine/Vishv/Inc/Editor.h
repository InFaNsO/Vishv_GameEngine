#pragma once
#ifndef INCLUDED_VISHV_EDITOR
#define INCLUDED_VISHV_EDITOR

#include "EditorRenderToWindow.h"

namespace Vishv
{
	class GameObject;
	class Service;
	class GameWorld;

	class EditorManager
	{
	public:
		static void StaticInitialize();
		static EditorManager* Get();
		static void StaticTerminate();
	public:
		void Initialize();
		void Terminate();
		void ShowExampleMenuFile();
		void DebugUI();
		void DrawSimpleDraw();
	private:
		void MenueBar();

		void MainDockingSpace();

		void HirarchyWindow();
		void InspectorWindow();

		void SceneWindow();

	private:
		friend class GameWorld;

		GameWorld* mWorld;
		
		GameObject* mCurrentGameObject = nullptr;
		Service* mCurrentService = nullptr;

		Editor::RenderToWindow mSceneRender;
		//add may be other renderers
	};
}

#endif 


