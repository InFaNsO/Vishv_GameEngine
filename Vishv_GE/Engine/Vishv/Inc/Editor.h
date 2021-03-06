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

		void BeginSceneRender();
		void EndSceneRender();

		void SetBackgroundColor(Vishv::Graphics::Color bgCol);

		Math::Vector2 GetRenderSpace();
		bool IsSimpleDraw() { return mDrawGizmos; }
	private:
		void MenueBar();

		void MainDockingSpace();

		void HirarchyWindow();
		void InspectorWindow();

		void SceneWindow();

		void SceneSettings();
		void HandleDomeSettings();

	private:
		friend class GameWorld;
		void SetStaticMembers();

		GameWorld* mWorld = nullptr;
		
		GameObject* mCurrentGameObject = nullptr;
		Service* mCurrentService = nullptr;

		Editor::RenderToWindow mSceneRender;
		//add may be other renderers


		bool mDrawGizmos = true;
		bool mShowDome = false;
	};
}

#endif 


