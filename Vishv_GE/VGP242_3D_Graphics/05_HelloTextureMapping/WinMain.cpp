#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;


void CameraUpdate(Vishv::Graphics::Camera &cam)
{
	const float move = 0.25f;
	const float rotate = 1.0f * Constans::DegToRad;
	if (GetAsyncKeyState(0x57))//w
	{
		cam.Walk(move * 10);
	}
	else if (GetAsyncKeyState(0x53))//s
	{
		cam.Walk(-move * 10);
	}
	else if (GetAsyncKeyState(0x41)) //a
	{
		cam.Strafe(-move);
	}
	else if (GetAsyncKeyState(0x44)) //d
	{
		cam.Strafe(move);
	}
	else if (GetAsyncKeyState(0x51)) //q
	{
		cam.Rise(move);
	}
	else if (GetAsyncKeyState(0x45)) //e
	{
		cam.Rise(-move);
	}

}

void MeshUpdate(Vishv::Graphics::MeshBuffer &mb)
{
	if (GetAsyncKeyState(0x33)) //3
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateCubePC(5.0f, 3.0f, 8.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x34)) //4
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreatePlanePC(6, 10, 1.0f, 1.5f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x35)) //5
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateCylinderPC(6, 14, 2.0f, 1.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x36)) //6
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateConePC(6, 14, 2.0f, 1.0f);
		mb.Initialize(mesh);
	}
	else if (GetAsyncKeyState(0x37)) //7
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateSpherePC(14, 14, 10.0f);
		mb.Initialize(mesh);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Texture", 1280, 720);

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);

	MeshPX space = Meshbuilder::CreateTorusUV(18, 14, 5.0f, 8.0f);
		
	Vishv::Graphics::ConstantBuffer cb;
	Vishv::Graphics::MeshBuffer		mb;
	Vishv::Graphics::PixelShader	ps;
	Vishv::Graphics::VertexShader	vs;
	Vishv::Graphics::Texture		tx;
	Vishv::Graphics::Sampler		sm;

	tx.Initialize(L"../../Assets/Images/earth_lights.jpg");
	sm.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	cb.Initialize();
	mb.Initialize(space);

	std::filesystem::path p = "../../Assets/Shaders/Texturing.fx";

	ps.Initialize(p);
	vs.Initialize(p, VertexPX::Format);

	/////////////////////////////////////////////////////////////////////////////////////

	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 5.0f, -40.0f });
	cam.SetDirection({ 0.0f, 0.0f, 1.0f });

	float theta = 0.0f;

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();

		CameraUpdate(cam);
		MeshUpdate(mb);

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}

		theta += 0.025f;

		cam.ComputeMatricies(1280.0f / 720.0f);

		GraphicsSystem::Get()->BeginRender();
		Matrix4 rotX = Matrix4::RotateMatrixX(180 * Constans::DegToRad);
		Matrix4 rotY = Matrix4::RotateMatrixY(theta);
		Matrix4 rotZ = Matrix4::RotateMatrixZ(0);

		Matrix4 mat[3];
		mat[0] = (rotX*rotY*rotZ).Transpose();
		mat[1] = cam.GetViewMatrix().Transpose();
		mat[2] = cam.GetPerspectiveMatrix().Transpose();

		cb.Bind(mat);
		mb.Bind();
		tx.BindPS();
		sm.BindPS();
		vs.Bind();
		ps.Bind();
		mb.Render();



		GraphicsSystem::Get()->EndRender();

	}

	GraphicsSystem::StaticTerminate();
	vs.Terminate();
	cb.Terminate();
	mb.Terminate();
	ps.Terminate();
	sm.Terminate();
	tx.Terminate();

	myWindow.Terminate();
	return 0;
}


