#ifndef INCLUDED_VISHV_APP_H
#define INCLUDED_VISHV_APP_H

#include "Scene.h"

namespace Vishv {

	class AppState;

	struct AppConfig
	{
		AppConfig() = default;
		AppConfig(std::string AppName)
			:appName(AppName)
		{
		}

		std::string appName = "Vishv";
		std::filesystem::path assetDirectory = L"../../Assets";
		uint32_t windowWidth = 1280;
		uint32_t windowHeight = 720;

		bool maximize = false;
		bool docking = true;
	};

	class App
	{
	public:
		void Run(AppConfig config);

		template <class StateType>
		void AddState(std::string name);
		void ChangeState(std::string name);

	private:
		void VishvDockSpace();
		void VishvUI();
		void VishvUI_ModelImporter();
		void VishvUI_ModelLoader();
		void VishvUI_SceneRender();
		void VishvUI_BufferData();
		void VishvUI_SceneObjects();

		void VishvSimpleDraw();
		void Terminate();

		AppConfig mAppConfig;
		Core::Window mWindow;
		
		
		std::map<std::string, std::unique_ptr<AppState>> mAppStates;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;

	private:
		//variable members for running
		void SetUpEngine(AppConfig config);
		void BasicRendering();

		Vishv::Graphics::MeshBuffer mDome;
		Vishv::Graphics::TextureID mDomeTex;
		Vishv::Graphics::Camera mSceneCamera;
		Vishv::Graphics::RenderTarget mGameSceneRT;
		uint32_t mSceneWidth;
		uint32_t mSceneHeight;


		Vishv::Graphics::Color mBGColor;

	private:
		//UI variables
		bool mDrawGizmos = true;
		bool mIsCustomRender = true;
		bool mIsSceneRender = false;
		bool mDrawGrid = false;
		bool mDrawDome = false;
	};

	template<class StateType>
	inline void Vishv::App::AddState(std::string name)
	{
		mAppStates.emplace(name, std::make_unique<StateType>());
	}
}

#endif // ! INCLUDED_VISHV_APP_H
