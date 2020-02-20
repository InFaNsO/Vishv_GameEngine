#include "EditState.h"

//imgui demo menue
static void ShowExampleMenuFile()
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
		static bool b = true;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::Checkbox("Check", &b);
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
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}


void EditState::Initialize()
{
	shouldStart = false;
}

void EditState::Update(float deltaTime)
{
	if (shouldStart)
	{
		VishvApp::ChangeState("MainState");
		return;
	}
}

void EditState::RenderSimpleDraw()
{
}

void EditState::ShowSceneView()
{

}

void EditState::SetMainWindow()
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

void EditState::RenderDebugUI()
{
	DrawMenueBar();
	SetMainWindow();
	//DoUI();
	MainSceneRender();

}

void EditState::DoUI()
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

	Vishv::Math::Vector3 rotationCamera;

	if (ImGui::CollapsingHeader("CameraTransform##SceneSettings"))
	{
		ImGui::DragFloat3("Position##Transform", &mSceneCamera.transform.mPosition.x, 0.1f);
		if (ImGui::DragFloat3("Rotation##Transform", &rotationCamera.x, 1.f))
		{
			if (rotationCamera.x != 0.0f)
				mSceneCamera.transform.RotateX(rotationCamera.x);
			if (rotationCamera.y != 0.0f)
				mSceneCamera.transform.RotateY(rotationCamera.y);
			if (rotationCamera.z != 0.0f)
				mSceneCamera.transform.RotateZ(rotationCamera.z);
		}

		if (ImGui::Button("Top"))
		{
			mSceneCamera.transform.mPosition = { 0.0f,25.0f,0.0f };
			mSceneCamera.transform.SetRotation(Vishv::Math::Quaternion({ 1.0f,0.0f,0.0f }, Vishv::Math::Constans::DegToRad * 90.0f));
		}
		if (ImGui::Button("Front"))
		{
			mSceneCamera.transform.mPosition = { 0.0f,0.0f,-25.0f };
			mSceneCamera.transform.SetRotation(Vishv::Math::Quaternion({ 1.0f,0.0f,0.0f }, Vishv::Math::Constans::DegToRad * 0.0f));
		}
		if (ImGui::Button("Left"))
		{
			mSceneCamera.transform.mPosition = { -25.0f,0.0f,0.0f };
			mSceneCamera.transform.SetRotation(Vishv::Math::Quaternion({ 0.0f,1.0f,0.0f }, Vishv::Math::Constans::DegToRad * -90.0f));
		}
	}
}

void EditState::MainSceneRender()
{
}

void EditState::DrawMenueBar()
{
	if (!ImGui::BeginMainMenuBar())
		return;
	if (ImGui::BeginMenu("File##MainMenue"))
	{
		ShowExampleMenuFile();
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit##MainMenue"))
	{
		ImGui::EndMenu();

	}

	ImGui::EndMainMenuBar();
}

void EditState::Render()
{
}

void EditState::Terminate()
{
}

void EditState::RenderScene()
{
}

void EditState::PostProcess()
{
}

