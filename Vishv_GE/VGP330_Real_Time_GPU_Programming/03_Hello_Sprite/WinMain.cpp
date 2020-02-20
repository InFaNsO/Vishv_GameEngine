#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>
#include <Input/Inc/Input.h>
#include <ImGui/Inc/imgui.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;
using namespace Vishv::Input;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello ImGui", 1280, 720);

	//Initialize the input system
	InputSystem::StaticInitialize(myWindow.GetWindowHandle());

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);
	DebugUI::StaticInitialize(myWindow.GetWindowHandle());
	SpriteRenderer::StaticInitialize();

	/////////////////////////////////////////////////////////////////////////////////////

	Texture tex;
	tex.Initialize(L"../../Assets/Images/sponge_bob.png");

	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 0.0f, -10.0f });
	cam.SetDirection({ 0.0f, 0.0f, 1.0f });
	cam.SetFarPlane(4000.0f);

	SimpleDraw::StaticInitialize(10000);

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();

		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

		//CameraUpdate(cam);
		//MeshUpdate(mb);



		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			done = true;
		}

		static auto lastTime = std::chrono::system_clock::now();
		auto currentTime = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count() / 1000;
		lastTime = currentTime;

		const float moveSpeed = 1.0f;
		const float turnSpeed = 0.10f;
		if (inputSystem->IsKeyDown(KeyCode::W))
			cam.Walk(moveSpeed * deltaTime);
		if (inputSystem->IsKeyDown(KeyCode::S))
			cam.Walk(-moveSpeed * deltaTime);
		if (inputSystem->IsKeyDown(KeyCode::D))
			cam.Strafe(moveSpeed * deltaTime);
		if (inputSystem->IsKeyDown(KeyCode::A))
			cam.Strafe(-moveSpeed * deltaTime);
		if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
		{
			cam.Yaw(inputSystem->GetMouseMoveX()   * turnSpeed * deltaTime * Constans::DegToRad);
			cam.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime * Constans::DegToRad);
		}



		GraphicsSystem::Get()->BeginRender();
		SimpleDraw::AddLine(Vector3(), { 100.0f, 0.0f, 0.0f }, Colors::Red);
		SimpleDraw::AddLine(Vector3(), { 0.0f, 100.0f, 0.0f }, Colors::Green);
		SimpleDraw::AddLine(Vector3(), { 0.0f, 0.0f, 100.0f }, Colors::Yellow);

		SimpleDraw::AddSphere({ 10.0f, 10.0f, 10.0f }, 50.0f, Colors::Black);

		SpriteRenderer::Get()->BeginRender();
		SpriteRenderer::Get()->Draw(tex, { 10.0f, 10.0f });
		SpriteRenderer::Get()->EndRender();

		SimpleDraw::Render(cam);

		DebugUI::BeginRender();
		ImGui::ShowDemoWindow();
		DebugUI::EndRender();

		GraphicsSystem::Get()->EndRender();
	}
	tex.Terminate();
	SpriteRenderer::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	SimpleDraw::StaticTerminate();
	InputSystem::StaticTerminate();
	DebugUI::StaticTerminate();
	myWindow.Terminate();
	return 0;
}
