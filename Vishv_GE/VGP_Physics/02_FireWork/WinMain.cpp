#include "Engine/Vishv/Inc/Vishv.h"

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;
using namespace Vishv::Input;
using namespace Vishv::Physics;

struct FireworkParticle
{
	MeshPC mParticle;
	Firework mFirework;
	Matrix4 mTransformation;
	Vishv::Graphics::MeshBuffer mb;
	Vishv::Graphics::ConstantBuffer cb;

	bool mIsDead = false;

	void Initialize(Fireworks::Ruleset rule, std::vector<Firework>& pyload, Vector3 position)
	{
		mParticle = Meshbuilder::CreateSphere(14, 14, 5.0f);
		mFirework.Initialize(pyload, rule, position);

		cb.Initialize();
		mb.Initialize(mParticle);
	}

	void Update(float deltaTime, const Matrix4& view, const  Matrix4 perspective)
	{
		mIsDead = mFirework.Update(deltaTime);
		Matrix4 mat[3];
		mat[0] = Matrix4::TranslateMatrix(mFirework.GetPosition()).Transpose();
		mat[1] = view;
		mat[2] = perspective;

		cb.Bind(mat);
		mb.Bind();
	}

	void Draw()
	{
		mb.Render();
	}

	void Terminate()
	{
		cb.Terminate();
		mb.Terminate();
	}
};

std::vector<FireworkParticle> cracker;

FireworkParticle start;

Fireworks::Ruleset MakeRuleSet(int type)
{
	Fireworks::Ruleset rs;
	switch (type)
	{
	case 1:
		rs.mMaxAge = 50.0f;
		rs.mMinVelocity = Vector3(0.5f, 0.4f, 0.0f);
		rs.mMaxVelocity = Vector3(6.0f, 6.0f, 0.0f);
		rs.mRuleNumeber = 1;
		rs.mDampening = 0.7f;
		break;
	case 2:
		rs.mMaxAge = 3;
		rs.mMinVelocity = Vector3(2.0f, 5.0f, 7.0f);
		rs.mMaxVelocity = Vector3(6.0f, 8.0f, 10.0f);
		rs.mRuleNumeber = 2;
		rs.mDampening = 0.5f;
		break;
	case 3:
		rs.mMaxAge = 10;
		rs.mMinVelocity = Vector3(3.0f, 4.0f, 3.0f);
		rs.mMaxVelocity = Vector3(6.0f, 6.0f, 8.0f);
		rs.mRuleNumeber = 3;
		rs.mDampening = 0.5f;
		break;
	default:
		break;
	}
	return rs;
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

	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	std::vector<Firework> pl;

	start.Initialize(MakeRuleSet(1), pl, { 0.0f, 5.0f, 5.0f });

	ps.Initialize("../../Assets/Shaders/DoTransform.fx");
	vs.Initialize("../../Assets/Shaders/DoTransform.fx", VertexPC::Format);


	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 0.0f, -30.0f });
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

		deltaTime = 0.03f;

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

		//correct this part
		vs.Bind();
		ps.Bind();

		if (!start.mIsDead)
		{
			start.Update(0.03f, cam.GetViewMatrix().Transpose(), cam.GetPerspectiveMatrix(1280.0f / 720.0f).Transpose());
			start.Draw();
			if (start.mIsDead)
			{
				for (auto it = start.mFirework.GetPayload().begin(); it != start.mFirework.GetPayload().end(); ++it)
				{
					FireworkParticle fp;
					fp.Initialize(it->GetRuleSet(), it->GetPayload(), start.mFirework.GetPosition());
					cracker.push_back(fp);
				}
			}
		}
		else
		{
			for (int i = 0; i < cracker.size(); ++i)
			{
				if (!cracker[i].mIsDead)
				{
					cracker[i].Update(deltaTime, cam.GetViewMatrix().Transpose(), cam.GetPerspectiveMatrix(1280.0f / 720.0f).Transpose());
					cracker[i].Draw();
					if (cracker[i].mIsDead)
					{
						for (auto it = cracker[i].mFirework.GetPayload().begin(); it != cracker[i].mFirework.GetPayload().end(); ++it)
						{
							FireworkParticle fp;
							fp.Initialize(it->GetRuleSet(), it->GetPayload(), cracker[i].mFirework.GetPosition());
							cracker.push_back(fp);
						}
					}
				}
			}
		}

		GraphicsSystem::Get()->EndRender();
	}
	for (int i = 0; i < cracker.size(); ++i)
	{
		cracker[i].Terminate();
	}
	start.Terminate();
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
