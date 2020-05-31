#include "Precompiled.h"
#include "Editor.h"

#include "GameWorld.h"
#include "GameObject.h"
#include "Service.h"
#include "CameraService.h"

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ModelConvertorTool.h"

#include "GizmoIm.h"

#pragma region Static Stuff
namespace
{
	using namespace Vishv;

	std::unique_ptr<Vishv::EditorManager> sInstance = nullptr;

	//for dome
	static Vishv::Graphics::MeshBuffer mDome;
	static Vishv::Graphics::TextureID mDomeTex;

	//for camera Service
	static Vishv::CameraSystem* camSer = nullptr;
	static Vishv::Components::CameraComponent* cam = nullptr;
	void NameSpaceInitialize(GameWorld* world)
	{
		camSer = world->GetService<CameraSystem>();
		cam = camSer->GetMainCamera().Get()->GetComponent<Components::CameraComponent>();

		mDome.Initialize(Vishv::Graphics::Meshbuilder::CreateSphereUV(12, 12, cam->GetCamera().GetFarPlane()));
		mDomeTex = Vishv::Graphics::TextureManager::Get()->LoadTexture("HDRI\\Hanger_Small\\hdr.jpg");
	}
	void UpdateMainCam()
	{
		static auto cameraGameObject = camSer->GetMainCamera();
		if (cameraGameObject != camSer->GetMainCamera())
		{
			cameraGameObject = camSer->GetMainCamera();
			cam = cameraGameObject.Get()->GetComponent<Components::CameraComponent>();
		}
	}

	void NameSpaceTerminate()
	{
		mDome.Terminate();
	}
}

void Vishv::EditorManager::StaticInitialize()
{
	if (!sInstance)
	{
		sInstance = std::make_unique<Vishv::EditorManager>();
		//Editor::ScreenGizmo::StaticInitialize();
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
		//Editor::ScreenGizmo::Terminate();
		sInstance->Terminate();
	}
}
void Vishv::EditorManager::SetStaticMembers()
{
	NameSpaceInitialize(mWorld);
	//Editor::ScreenGizmo::Get()->CamService = camSer;
}

#pragma endregion


void Vishv::EditorManager::BeginSceneRender()
{
	mSceneRender.mRenderTarget.BeginRender();
}

void Vishv::EditorManager::EndSceneRender()
{
	mSceneRender.mRenderTarget.EndRender();
}


void Vishv::EditorManager::Initialize()
{
	mSceneRender.Initialize();
	Editor::ModelConvertor::StaticInitialize();
}

void Vishv::EditorManager::Terminate()
{
	mSceneRender.Terminate();
}

void Vishv::EditorManager::DrawSimpleDraw()
{
	if (!mDrawGizmos)
		return;

	UpdateMainCam();

	//Graphics::SimpleDraw::AddSphere({}, 5.0f, Vishv::Graphics::Colors::White);

	Graphics::SimpleDraw::Render(cam->GetCamera());
}

void Vishv::EditorManager::DebugUI()
{
	//call all the UI Functions
	MainDockingSpace();
	MenueBar();

	HirarchyWindow();
	InspectorWindow();

	SceneWindow();
	SceneSettings();

	Editor::ModelConvertor::Get()->DoUI();
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
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("(dummy menu)", NULL, false, false);
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Convert Model"))
			{
				Editor::ModelConvertor::Get()->Open();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Vishv::EditorManager::ShowExampleMenuFile()
{
	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}

	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Colors"))
	{
		float sz = ImGui::GetTextLineHeight();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
			ImGui::Dummy(ImVec2(sz, sz));
			ImGui::SameLine();
			ImGui::MenuItem(name);
		}
		ImGui::EndMenu();
	}

	// Here we demonstrate appending again to the "Options" menu (which we already created above)
	// Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
	// In a real code-base using it would make senses to use this feature from very different code locations.
	if (ImGui::BeginMenu("Options")) // <-- Append!
	{
		static bool b = true;
		ImGui::Checkbox("SomeOption", &b);
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}
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
	{
		mCurrentGameObject->DebugUI();
	}
	ImGui::End();
}

void Vishv::EditorManager::SceneWindow()
{
	auto gs = Vishv::Graphics::GraphicsSystem::Get();

	ImGui::SetNextWindowSize({gs->GetBackBufferWidth()* 0.6f, gs->GetBackBufferHeight() * 0.6f});
	ImGui::Begin("Scene");
	

	ImVec2 vMin = ImGui::GetWindowContentRegionMin();
	ImVec2 vMax = ImGui::GetWindowContentRegionMax();

	if (mCurrentGameObject)
	{
		//Editor::ScreenGizmo::Get()->currentObjectTransform = mCurrentGameObject->GetComponent<Vishv::Components::TransformComponent>();
		//Editor::ScreenGizmo::Get()->Update();
	}

	float windowWidth = vMax.x - vMin.x;
	float windowHeight = vMax.y - vMin.y;


//	mWorld->GetService<CameraSystem>()->SetWidthNHeight(windowWidth, windowHeight);

	///mSceneRender.Resize();
	mSceneRender.DoUI();
	
	ImGui::End();
}

Math::Vector2 Vishv::EditorManager::GetRenderSpace()
{
	return Math::Vector2(static_cast<float>(mSceneRender.mWindowWidth), static_cast<float>(mSceneRender.mWindowWidth));
}

void Vishv::EditorManager::SceneSettings()
{
	ImGui::Begin("SceneSettings");

	//ImGui::Checkbox("Simple Draw", &mDrawGizmos);
	//ImGui::Checkbox("Use Skybox", &mShowDome);
	//
	//if (!mShowDome && ImGui::CollapsingHeader("Set Background Color"))
	//{
	//	static Vishv::Graphics::Color bgColor = Vishv::Graphics::Colors::Black;
	//	if (ImGui::ColorEdit4("BackGround Color", &bgColor.r))
	//	{
	//		Vishv::Graphics::GraphicsSystem::Get()->SetBackGroundColor(bgColor);
	//		mSceneRender.mRenderTarget.SetBackGroundColor(bgColor);
	//	}
	//}
	ImGui::End();
}

void Vishv::EditorManager::SetBackgroundColor(Vishv::Graphics::Color bgCol)
{
	mSceneRender.mRenderTarget.SetBackGroundColor(bgCol);
}

void Vishv::EditorManager::HandleDomeSettings()
{
	if (!mShowDome)
		return;

	UpdateMainCam();

	Vishv::Graphics::EffectsManager::Get()->BindEffect(Vishv::Graphics::EffectType::Texturing);
	auto view = cam->GetCamera().GetViewMatrix();
	auto proj = cam->GetCamera().GetPerspectiveMatrix();

	auto transform = Vishv::Math::Matrix4::Transpose(Vishv::Math::Matrix4::TranslateMatrix(cam->GetCamera().GetPosition()) * view * proj);

	Vishv::Graphics::EffectsManager::Get()->GetBufferData(Vishv::Graphics::EffectType::Texturing)->GetTextureing()->wvp = transform;
	Vishv::Graphics::EffectsManager::Get()->Set(Vishv::Graphics::EffectType::Texturing);
	Vishv::Graphics::EffectsManager::Get()->BindBuffer(Vishv::Graphics::EffectType::Texturing);

	Vishv::Graphics::TextureManager::Get()->GetTexture(mDomeTex)->BindPS(0);
	Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS();

	Vishv::Graphics::RasterizerManager::Get()->ChangeState("FrontSolid");
	mDome.Render();
	Vishv::Graphics::RasterizerManager::Get()->ChangeState("BackSolid");
}

