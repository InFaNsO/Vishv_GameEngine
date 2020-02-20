#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>
#include <Input/Inc/Input.h>
#include <ImGui/Inc/imgui.h>
#include <Physics/Inc/Physics.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;
using namespace Vishv::Input;
using namespace Vishv::Physics;

enum class BallisticType
{
	Pistol,
	Artillery,
	Fireball,
	Laser
};

BallisticType BulletType = BallisticType::Pistol;
Particle bulletParticle;

void ShootBullet(const Vector3& pos)
{
	bulletParticle.SetPosition(pos);
}

void SetBullet(BallisticType type)
{
	switch (type)
	{
	case BallisticType::Pistol:
		bulletParticle.SetMass(2.0f);
		bulletParticle.SetVelocity({ 0.0f,0.0f, 35.0f });
		bulletParticle.SetAcceleration({ 0.0f, -1.0f, 0.0f });
		bulletParticle.SetDampening(0.99f);
		break;
	case BallisticType::Artillery:
		bulletParticle.SetMass(200.0f);
		bulletParticle.SetVelocity({ 0.0f,30.0f, 40.0f });
		bulletParticle.SetAcceleration({ 0.0f, -20.0f, 0.0f });
		bulletParticle.SetDampening(0.99f);
		break;
	case BallisticType::Fireball:
		bulletParticle.SetMass(1.0f);
		bulletParticle.SetVelocity({ 0.0f,0.0f, 10.0f });
		bulletParticle.SetAcceleration({ 0.0f, 0.60f, 0.0f });
		bulletParticle.SetDampening(0.9f);
		break;
	case BallisticType::Laser:
		bulletParticle.SetMass(0.1f);
		bulletParticle.SetVelocity({ 0.0f,0.0f, 100.0f });
		bulletParticle.SetAcceleration({ 0.0f, 0.0f, 0.0f });
		bulletParticle.SetDampening(0.99f);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Ballistics", 1280, 720);

	//Initialize the input system
	InputSystem::StaticInitialize(myWindow.GetWindowHandle());

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);
	DebugUI::StaticInitialize(myWindow.GetWindowHandle());
	SpriteRenderer::StaticInitialize();

	/////////////////////////////////////////////////////////////////////////////////////

	MeshPC bullet = Meshbuilder::CreateSphere(14, 14, 2);//  (3, 5, 3, 3);
	Matrix4 bulletTransformation;
	SetBullet(BallisticType::Pistol);
	ShootBullet({ 0.0f, 0.0f, 0.0f });

	Vishv::Graphics::ConstantBuffer cb;
	Vishv::Graphics::MeshBuffer mb;
	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	cb.Initialize();
	mb.Initialize(bullet);
	ps.Initialize("../../Assets/Shaders/DoTransform.fx");
	vs.Initialize("../../Assets/Shaders/DoTransform.fx", VertexPC::Format);


	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 0.0f, -10.0f });
	cam.SetDirection({ 0.0f, 0.0f, 1.0f });
	cam.SetFarPlane(4000.0f);

	SimpleDraw::StaticInitialize(10000);

	float theta = 0.0f;

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();

		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

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
		if (inputSystem->IsMouseDown(MouseButton::LBUTTON))
		{
			Vector3 v(cam.GetDirection());
			v *= 3.0f;
			v += cam.GetPosition();

			ShootBullet(v);
		}
		if (inputSystem->IsKeyDown(KeyCode::ONE))
		{
			SetBullet(BallisticType::Pistol);
		}
		if (inputSystem->IsKeyDown(KeyCode::TWO))
		{
			SetBullet(BallisticType::Artillery);
		}
		if (inputSystem->IsKeyDown(KeyCode::THREE))
		{
			SetBullet(BallisticType::Fireball);
		}
		if (inputSystem->IsKeyDown(KeyCode::FOUR))
		{
			SetBullet(BallisticType::Laser);
		}

		bulletParticle.Update(0.033f);

		theta += 0.025f;


		GraphicsSystem::Get()->BeginRender();

		Matrix4 rotX = Matrix4::RotateMatrixX(theta);
		Matrix4 rotY = Matrix4::RotateMatrixY(theta);
		Matrix4 rotZ = Matrix4::RotateMatrixZ(theta);

		Matrix4 mat[3];
		//	mat[0] = Matrix4::Identity();
		mat[0] = Matrix4::TranslateMatrix(bulletParticle.GetPosition()).Transpose();
		mat[1] = cam.GetViewMatrix().Transpose();
		mat[2] = cam.GetPerspectiveMatrix(1280.0f / 720.0f).Transpose();


		//correct this part
		cb.Bind(mat);
		mb.Bind();
		vs.Bind();
		ps.Bind();
		mb.Render();


		SimpleDraw::AddSphere({ 10.0f, 10.0f, 10.0f }, 50.0f, Colors::Black);
		
		SimpleDraw::Render(cam);
		//
		//
		//DebugUI::BeginRender();
		//ImGui::ShowDemoWindow();
		//DebugUI::EndRender();

		GraphicsSystem::Get()->EndRender();
	}

	cb.Terminate();
	mb.Terminate();
	ps.Terminate();
	vs.Terminate();

	SpriteRenderer::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	SimpleDraw::StaticTerminate();
	InputSystem::StaticTerminate();
	DebugUI::StaticTerminate();
	myWindow.Terminate();
	return 0;
}
