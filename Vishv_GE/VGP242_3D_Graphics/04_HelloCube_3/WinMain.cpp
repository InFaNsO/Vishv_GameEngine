#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;


void CameraUpdate(Vishv::Graphics::Camera &cam)
{
	cam.ComputeMatricies(1280.0f / 720.0f);

	const float move = 0.25f;
	const float rotate = 1.0f * Constans::DegToRad;
	if (GetAsyncKeyState(0x57))//w
	{
		cam.Walk(move);
	}
	else if (GetAsyncKeyState(0x53))//s
	{
		cam.Walk(-move);
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
	else if (GetAsyncKeyState(0x5A)) //z
	{
		cam.Yaw(rotate);
	}
	else if (GetAsyncKeyState(0x58)) //x
	{
		cam.Yaw(-rotate);
	}
	else if (GetAsyncKeyState(0x31)) //1
	{
		cam.Pitch(-rotate);
	}
	else if (GetAsyncKeyState(0x32)) //2
	{
		cam.Pitch(rotate);
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
	else if (GetAsyncKeyState(0x38)) //8
	{
		mb.Terminate();
		MeshPC mesh = Meshbuilder::CreateTorusPC(18, 14, 5.0f, 8.0f);
		mb.Initialize(mesh);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Triangle", 1280, 720);

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);

	MeshPC Cylender = Meshbuilder::CreateSpherePC(14, 14, 10);//  (3, 5, 3, 3);
	MeshPC cube = Meshbuilder::CreateCubePC(5, 4, 3);

	Vishv::Graphics::ConstantBuffer cb;
	Vishv::Graphics::MeshBuffer mb;
	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	cb.Initialize();
	mb.Initialize(Cylender);
	ps.Initialize("../../Assets/Shaders/DoTransform.fx");
	vs.Initialize("../../Assets/Shaders/DoTransform.fx", VertexPC::Format);

	/////////////////////////////////////////////////////////////////////////////////////

	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 5.0f, -40.0f });
	cam.SetDirection({ 0.0f, 0.0f, 1.0f });

	float theta = 0.0f;

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();
		Vishv::Math::Matrix4 transformMatrix(Vishv::Math::Matrix4::Identity());
		Vishv::Math::Matrix4 transformMatrixCube(Vishv::Math::Matrix4::Identity());

		CameraUpdate(cam);
		MeshUpdate(mb);

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}

		theta += 0.025f;

		GraphicsSystem::Get()->BeginRender();
		Matrix4 rotX = Matrix4::RotateMatrixX(theta);
		Matrix4 rotY = Matrix4::RotateMatrixY(theta);
		Matrix4 rotZ = Matrix4::RotateMatrixZ(theta);

		Matrix4 mat[3];
		//	mat[0] = Matrix4::Identity();
		mat[0] = (rotX*rotY*rotZ).Transpose();
		mat[1] = cam.GetViewMatrix().Transpose();
		mat[2] = cam.GetPerspectiveMatrix().Transpose();

		cb.Bind(mat);
		mb.Bind();
		vs.Bind();
		ps.Bind();
		mb.Render();

		GraphicsSystem::Get()->EndRender();

	}

	//SafeRelease(vertexShader);
	//SafeRelease(inputLayout);
	//SafeRelease(pixelShader);
	//SafeRelease(vertexBuffer);
	GraphicsSystem::StaticTerminate();
	vs.Terminate();
	cb.Terminate();
	mb.Terminate();
	ps.Terminate();

	myWindow.Terminate();
	return 0;
}


