#include "Precompiled.h"
#include "Editor.h"

#include "GameWorld.h"
#include "GameObject.h"
#include "Service.h"
#include "CameraService.h"

#include "TransformComponent.h"

namespace
{
	std::unique_ptr<Vishv::EditorManager> sInstance = nullptr;
}

void Vishv::EditorManager::StaticInitialize()
{
	if (!sInstance)
	{
		sInstance = std::make_unique<Vishv::EditorManager>();
		sInstance->Initialize();
	}
}

Vishv::EditorManager* Vishv::EditorManager::Get()
{
	return sInstance.get();
}

void Vishv::EditorManager::StaticTerminate()
{
	if (sInstance)
	{
		sInstance->Terminate();
	}
}



void Vishv::EditorManager::Initialize()
{
	mSceneRender.Initialize();
}

void Vishv::EditorManager::Terminate()
{
	mSceneRender.Terminate();
}

void Vishv::EditorManager::DebugUI()
{
	//call all the UI Functions
	MainDockingSpace();
	//MenueBar();

	HirarchyWindow();
	InspectorWindow();

	SceneWindow();
}

void Vishv::EditorManager::MainDockingSpace()
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
void Vishv::EditorManager::MenueBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}


void Vishv::EditorManager::HirarchyWindow()
{
	ImGui::Begin("Heirarchy");
	if (ImGui::CollapsingHeader("Services"))
	{
		for (auto& service : mWorld->mServices)
		{
			if (ImGui::Button(service.get()->GetTypeID().c_str()))
			{
				mCurrentGameObject = nullptr;
				mCurrentService = service.get();
			}
		}
	}
	if (ImGui::CollapsingHeader("Game Objects"))
	{
		for (auto& go : mWorld->mUpdateList)
		{
			if (ImGui::Button(go->mName.c_str()))
			{
				mCurrentService = nullptr;
				mCurrentGameObject = go;
			}
		}
	}

	if (ImGui::Button("Add Game Object"))
	{
		mCurrentGameObject = mWorld->CreateGameObject();
		mCurrentGameObject->AddComponent<Components::TransformComponent>();
		mCurrentService = nullptr;
	}
	ImGui::End();
}

void Vishv::EditorManager::InspectorWindow()
{
	ImGui::Begin("Inspector");

	if (mCurrentService)
	{
		mCurrentService->DoUI(mCurrentService, *mCurrentService->GetMetaClass());
		mCurrentService->DebugUI();
	}
	else if (mCurrentGameObject)
		mCurrentGameObject->DebugUI();
	
	ImGui::End();
}

void Vishv::EditorManager::SceneWindow()
{
	auto gs = Vishv::Graphics::GraphicsSystem::Get();

	ImGui::SetNextWindowSize({gs->GetBackBufferWidth()* 0.6f, gs->GetBackBufferHeight() * 0.6f});
	ImGui::Begin("Scene");
	

	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();


	float windowWidth = vMax.x - vMin.x;
	float windowHeight = vMax.y - vMin.y;


//	mWorld->GetService<CameraSystem>()->SetWidthNHeight(windowWidth, windowHeight);

	//mSceneRender.Resize();
	mSceneRender.DoUI();
	
	ImGui::End();
}

