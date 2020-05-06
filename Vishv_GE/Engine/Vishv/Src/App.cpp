#include "Precompiled.h"
#include "App.h"
#include "AppState.h"
#include "Common.h"
#include "GlobalHeaders.h"
#include "MetaRegistration.h"
#include "GameWorld.h"
#include "Editor.h"

//Vishv::Time::DeltaTime = 0.0f;

namespace
{
	std::unique_ptr<ImGui::FileBrowser> modelImporterFileBrowser = nullptr;
}

void Vishv::App::Run(AppConfig config)
{
	LOG("App Starting .......");
	LOG("Registering Core Meta.");
	Core::StaticMetaRegister();
	LOG("Registering Math Meta.");
	Math::StaticMetaRegister();
	LOG("Registering Graphics Meta.");
	//graphics
	LOG("Registering AI Meta.");
	AI::StaticMetaRegister();
	LOG("Registering Vishv Meta.");
	StaticMetaRegister();

	LOG("Creating Window.");
	mWindow.Initialize(GetModuleHandle(NULL), config.appName.c_str(), config.windowWidth, config.windowHeight, config.maximize);

	//set up engine stuff
	LOG("Setting Up Engine.");
	SetUpEngine(config);

	//setup file browser
	modelImporterFileBrowser = std::make_unique<ImGui::FileBrowser>(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_SelectDirectory);
	modelImporterFileBrowser->SetTitle("Model Import");
	modelImporterFileBrowser->SetPwd(config.assetDirectory);

	if (mNextState)
		mCurrentState = mNextState;
	else	
		mCurrentState = mAppStates.begin()->second.get();
	
	LOG("Registering App Meta.");
	mCurrentState->MetaRegister();
	LOG("Initializing Game World.");
	//mCurrentState->mGameWorld.Initialize(1000);
	
	mCurrentState->Initialize();
	mNextState = nullptr;

	bool done = false;
	while (!done)
	{
		done = mWindow.ProcessMessage();

		if (done)
			break;

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState,nullptr);
			mCurrentState->Initialize();
		}

		Core::Time::Get()->Update();

		auto inputSystem = Vishv::Input::InputSystem::Get();
		inputSystem->Update();

		mCurrentState->mGameWorld.Update();
		mCurrentState->Update();

		Vishv::Graphics::GraphicsSystem::Get()->BeginRender();

		//BasicRendering();
		mCurrentState->mGameWorld.Render();
		mCurrentState->Render();

		
		if (mDrawGizmos)
		{
			mCurrentState->mGameWorld.SimpleDraw();
			mCurrentState->RenderSimpleDraw();
			VishvSimpleDraw();
		}

		Vishv::Graphics::DebugUI::BeginRender();
		//modelImporterFileBrowser->Display();
		//VishvDockSpace();
		//VishvUI();
		//mCurrentState->mGameWorld.DebugUI();
		EditorManager::Get()->DebugUI();
		mCurrentState->RenderDebugUI();
		Vishv::Graphics::DebugUI::EndRender();

		//add other renderers
		Vishv::Graphics::GraphicsSystem::Get()->EndRender();
	}

	Terminate();
}

void Vishv::App::ChangeState(std::string name)
{
	if (auto iter = mAppStates.find(name); iter != mAppStates.end())
		mNextState = iter->second.get();
}

void Vishv::App::VishvSimpleDraw()
{
	if (mDrawGrid)
	{
		for (float i = -50.0f; i < 50.0f; ++i)
		{
			Vishv::Graphics::SimpleDraw::AddLine({ i, 0.0f, -50.0f }, { i, 0.0f, 50.0f }, Vishv::Graphics::Colors::Gray);
			Vishv::Graphics::SimpleDraw::AddLine({ -50.0f, 0.0f, i }, { 50.0f, 0.0f, i }, Vishv::Graphics::Colors::Gray);
		}
	}

	Vishv::Graphics::SimpleDraw::Render(mSceneCamera);
}

void Vishv::App::VishvDockSpace()
{
	ImGuiViewport* viewPort = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewPort->Pos);
	ImGui::SetNextWindowSize(viewPort->Size);
	ImGui::SetNextWindowViewport(viewPort->ID);

	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Main", nullptr, window_flags);
	ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	ImGui::End();

	ImGui::PopStyleVar(3);
}

void Vishv::App::VishvUI()
{
	ImGui::Begin("Scene Settings");
	if (ImGui::CollapsingHeader("Options##SceneSettings"))
	{
		ImGui::Checkbox("Draw Gizmos", &mDrawGizmos);
		ImGui::Checkbox("Custom Render", &mIsCustomRender);
		ImGui::Checkbox("Scene Render", &mIsSceneRender);
		ImGui::Checkbox("Draw Grid", &mDrawGrid);
		ImGui::Checkbox("Show Dome", &mDrawDome);

		if (!mDrawDome)
		{
			if (ImGui::ColorEdit4("BackGround Color", &mBGColor.r))
			{
				Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);
				mGameSceneRT.SetBackGroundColor(mBGColor);
			}
		}
	}
	ImGui::End();

	VishvUI_SceneRender();
}
/*
void Vishv::App::VishvUI_ModelImporter()
{
	static std::filesystem::path importFile;
	static std::filesystem::path exportFile;
	static std::filesystem::path fileexe = "..\\..\\Debug\\ModelImporter.exe";

	static bool isImport = false;
	static bool isExport = false;
	static bool runf = false;

	if (ImGui::CollapsingHeader("ModelImporter##SceneSettings"))
	{
		if (ImGui::Button("ImportFile"))
		{
			modelImporterFileBrowser->SetTypeFilters({ ".fbx" });
			modelImporterFileBrowser->Open();
			isImport = true;
		}
		if (ImGui::Button("ExportFile"))
		{
			modelImporterFileBrowser->SetTypeFilters({ ".vmesh" });
			modelImporterFileBrowser->Open();
			isExport = true;
		}
		if (ImGui::Button("Run"))
		{
			std::string command = "start " + fileexe.string() + " " + importFile.string() + " " + exportFile.string();
			system(command.c_str());
		}
	}
	if (modelImporterFileBrowser->HasSelected() && (isImport || isExport))
	{
		if (isImport)
			importFile = modelImporterFileBrowser->GetSelected();
		if (isExport)
			exportFile = modelImporterFileBrowser->GetSelected();
		modelImporterFileBrowser->ClearSelected();
		modelImporterFileBrowser->Close();

		isImport = false;
		isExport = false;
	}
}

void Vishv::App::VishvUI_ModelLoader()
{
	static char loadFile[128]{};

	static bool isLoadModel = false;
	static bool isLoadAnim = false;
	static std::filesystem::path modelDirectory;
	if (ImGui::CollapsingHeader("Model Loader##SceneSettings"))
	{
		ImGui::InputText("Model Name##ModelLoader", loadFile, std::size(loadFile));
		if (ImGui::Button("Load Model Directory##ModelLoader"))
		{
			modelImporterFileBrowser->Open();
			isLoadModel = true;
		}
		if (ImGui::Button("Load Aniamtion##ModelLoader"))
		{
			modelImporterFileBrowser->SetTypeFilters({ ".vanim" });
			modelImporterFileBrowser->Open();
			isLoadAnim = true;
		}
		if (ImGui::Button("New Animation Set##ModelLoader"))
		{
			mCurrentState->scene.mAnimationSets.push_back(std::make_unique<Vishv::Graphics::AnimationSet>());
		}
	}
	if (isLoadModel && modelImporterFileBrowser->HasSelected())
	{
		modelDirectory = modelImporterFileBrowser->GetSelected();
		modelImporterFileBrowser->ClearSelected();
		modelDirectory.remove_filename();
		isLoadModel = false;
		//load mesh
		std::string meshName = loadFile;
		Vishv::Math::Transform transformObject;
		mCurrentState->scene.mObjects.push_back(std::make_unique<Vishv::Graphics::Object3D>(transformObject));
		auto object = mCurrentState->scene.mObjects.back().get();
		object->Set(modelDirectory / (meshName + ".vmesh"));

		//Vishv::Graphics::MeshIO mio;
		//if (!mio.LoadMeshGeneral(modelDirectory / (meshName + ".vmesh")))
		//	return;

		//mio.GetModel(object->mModel.model);
		//load skeleton
		Vishv::Graphics::SkeletonIO sio;
		if (!sio.LoadSkeleton(modelDirectory / (meshName + ".vskel"), object->mModel.skeleton))
			return;
	}
	if (isLoadAnim && modelImporterFileBrowser->HasSelected())
	{
		modelDirectory = modelImporterFileBrowser->GetSelected();
		modelImporterFileBrowser->ClearSelected();
		isLoadAnim = false;

		std::string name = loadFile;
		name += ".vanim";

		mCurrentState->scene.mAnimationSets.back()->animationClips.push_back(std::make_unique<Vishv::Graphics::AnimationClip>());
		Vishv::Graphics::AnimationIO aio;
		if (aio.LoadAnimation(modelDirectory / name, *mCurrentState->scene.mAnimationSets.back()->animationClips.back().get()))
		{
			mCurrentState->scene.mObjects[0]->mModel.animations = mCurrentState->scene.mAnimationSets[0].get();
			return;
		}
	}
}
*/

void Vishv::App::VishvUI_SceneRender()
{
	//moved into editor SceneWindow
}
/*
void Vishv::App::VishvUI_BufferData()
{
	ImGui::Begin("Lighting Setings");

	auto em = Vishv::Graphics::EffectsManager::Get()->GetBufferData(mCurrentState->scene.currentEffect);
	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(mCurrentState->scene.currentEffect) & Vishv::Graphics::EffectBufferType::EBTYPE_LIGHT)
	{
		//show Light controls
		if (ImGui::CollapsingHeader("Light"))
		{
			bool changed = false;
			if (ImGui::DragFloat3("Direction X##Light", &em->GetLightData()->position_Direction.x, 0.01f, -1.0f, 1.0f))
			{
				em->GetLightData()->position_Direction.Normalize();
			}
			ImGui::ColorEdit4("Ambient##Light", &em->GetLightData()->ambient.x);
			ImGui::ColorEdit4("Diffuse##Light", &em->GetLightData()->diffuse.x);
			ImGui::ColorEdit4("Specular##Light", &em->GetLightData()->specular.x);
		}
	}
	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(mCurrentState->scene.currentEffect) & Vishv::Graphics::EffectBufferType::EBTYPE_MATERIAL)
	{
		//show Material controls
		if (ImGui::CollapsingHeader("Material"))
		{
			ImGui::ColorEdit4("Ambient##Material", &em->GetMaterialData()->ambient.x);
			ImGui::ColorEdit4("Diffuse##Material", &em->GetMaterialData()->diffuse.x);
			ImGui::ColorEdit4("Specular##Material", &em->GetMaterialData()->specular.x);
			ImGui::DragFloat("Power##Material", &em->GetMaterialData()->power);
		}
	}
	if (Vishv::Graphics::EffectsManager::Get()->GetBufferType(mCurrentState->scene.currentEffect) & Vishv::Graphics::EffectBufferType::EBTYPE_OPTIONS)
	{
		if (ImGui::CollapsingHeader("Options"))
		{
			bool isNormal = em->GetOptionsData()->isNormal > 0.0f ? true : false;
			ImGui::DragFloat("Option 1##Options", &em->GetOptionsData()->displacement);
			if (ImGui::Checkbox("Option 2##Options", &isNormal))
			{
				em->GetOptionsData()->isNormal = isNormal ? 1.0f : 0.0f;
			}
			ImGui::DragFloat("Option 3##Options", &em->GetOptionsData()->padding[0]);
			ImGui::DragFloat("Option 4##Options", &em->GetOptionsData()->padding[1]);
		}
	}

	ImGui::End();
}

void Vishv::App::VishvUI_SceneObjects()
{
	ImGui::Begin("Scene Objects");

	std::string name = "3D Object ";

	for (size_t i = 0; i < mCurrentState->scene.mObjects.size(); ++i)
	{
		std::string title = name + std::to_string(i);
		if (ImGui::CollapsingHeader(title.c_str()))
		{
			ImGui::DragFloat3("Position##Objects", &mCurrentState->scene.mObjects[i]->transform.mPosition.x, 0.1f);

			//Vishv::Math::Vector3 rot(mCurrentState->scene.mObjects[i]->transform.rotationDegree.x * 2.0f,
			//	mCurrentState->scene.mObjects[i]->transform.rotationDegree.y * 2.0f,
			//	mCurrentState->scene.mObjects[i]->transform.rotationDegree.z * 2.0f);
			//if (ImGui::DragFloat3("Rotation##Objects", &rot.x, 1.f))
			//{
			//	mCurrentState->scene.mObjects[i]->transform.rotationDegree = rot * 0.5f;
			//
			//	mCurrentState->scene.mObjects[i]->transform.RotateX(rot.x);
			//	mCurrentState->scene.mObjects[i]->transform.RotateY(rot.y);
			//	mCurrentState->scene.mObjects[i]->transform.RotateZ(rot.z);
			//}

			if (mCurrentState->scene.mObjects[i]->mModel.animations == nullptr)
				continue;

			if (ImGui::CollapsingHeader("Animations##Objects"))
			{
				auto anims = mCurrentState->scene.mObjects[i]->mModel.animations;
				for (size_t j = 0; j < anims->animationClips.size(); ++j)
				{
					ImGui::Checkbox("Looping", &anims->animationClips[j]->isLooping);
					if (ImGui::Button(anims->animationClips[j]->name.c_str()))
					{
						mCurrentState->scene.mObjects[i]->mModel.playAnimations.push_back({ static_cast<int>(j),0.0f });
					}
				}
			}
		}
	}

	if (ImGui::CollapsingHeader("All Animations"))
	{
		
	}

	ImGui::End();
}
*/

void Vishv::App::SetUpEngine(AppConfig config)
{
	//hard code for now
	//mSceneCamera.transform.mPosition = { 50.0f, 100.0f,50.0f };

	LOG("Initializing Core System");
	Vishv::Core::Time::StaticInitialize();

	LOG("Initializing Input System");
	Vishv::Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	LOG("Initializing Graphics Systems");
	Vishv::Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Vishv::Graphics::EffectsManager::StaticInitialize();
	Vishv::Graphics::TextureManager::StaticInitialize(mAppConfig.assetDirectory / "Images");
	Vishv::Graphics::SamplerManager::StaticInitialize();
	Vishv::Graphics::SimpleDraw::StaticInitialize(99999);
	Vishv::Graphics::DebugUI::StaticInitialize(mWindow.GetWindowHandle(), config.docking);
	Vishv::Graphics::SpriteRenderer::StaticInitialize();
	Vishv::Graphics::BlendManager::StaticInitialize();
	Vishv::Graphics::RasterizerManager::StaticInitialize();

	Vishv::EditorManager::StaticInitialize();


	LOG("Initializing Shader Effects");
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::PostProcessing);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Merge);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Standard);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Skinning);
	Vishv::Graphics::EffectsManager::Get()->AddEffect(Vishv::Graphics::EffectType::Mixamo);

	//set up render target for the scene window
	mSceneHeight = static_cast<uint32_t>(Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferHeight() * 0.7f);
	mSceneWidth = static_cast<uint32_t>(Vishv::Graphics::GraphicsSystem::Get()->GetBackBufferWidth() * 0.7f);
	mGameSceneRT.Initialize(mSceneWidth, mSceneHeight,
		Vishv::Graphics::RenderTarget::Format::RGBA_U8);


	mBGColor = Vishv::Graphics::Colors::LightGray;
	Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(mBGColor);

	mDome.Initialize(Vishv::Graphics::Meshbuilder::CreateSphereUV(12, 12, 500.0f));
	mDomeTex = Vishv::Graphics::TextureManager::Get()->LoadTexture("space.jpg");
}

void Vishv::App::Terminate()
{
	mCurrentState->Terminate();
	Vishv::Graphics::RasterizerManager::StaticTerminate();
	Vishv::Graphics::BlendManager::StaticTerminate();
	Vishv::Graphics::SpriteRenderer::StaticTerminate();
	Vishv::Graphics::GraphicsSystem::StaticTerminate();
	Vishv::Graphics::TextureManager::StaticTerminate();
	Vishv::Graphics::SamplerManager::StaticTerminate();
	Vishv::Graphics::SimpleDraw::StaticTerminate();
	Vishv::Input::InputSystem::StaticTerminate();
	Vishv::Graphics::DebugUI::StaticTerminate();
	Vishv::Graphics::EffectsManager::StaticTerminate();
	Vishv::EditorManager::StaticTerminate();

	mGameSceneRT.Terminate();
	mDome.Terminate();
	mWindow.Terminate();
}

