#include <Vishv/Inc/Vishv.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;

struct Vert
{
	Vector3 position;
	float r, g, b, a;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Triangle", 1280, 720);

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);

	MeshPC mesh = Meshbuilder::CreateCubePC(6.f, 10.f, 1.0f);

	//Define the triangle to draw
	//Vishv::Graphics::Vertex vertices[] =
	//{
	//	{{0.0f, 0.2f, 0.0f}, Vishv::Math::Vector4::Color::Cyan()},			//Top Left Front
	//	{{0.0f, -0.2f, 0.0f}, Vishv::Math::Vector4::Color::LightRed()},		//buttom Left Front
	//	{{0.4f, -0.2f, 0.0f}, Vishv::Math::Vector4::Color::Teal()},			//Buttom Right Front
	//	{{0.4f, 0.2f, 0.0f}, Vishv::Math::Vector4::Color::Navy()},			//Top Right Front
	//
	//	{{0.0f, 0.2f, 0.4f}, Vishv::Math::Vector4::Color::Cyan()},			//Top Left		Back
	//	{{0.0f, -0.2f, 0.4f}, Vishv::Math::Vector4::Color::LightRed()},		//buttom Left	Back
	//	{{0.4f, -0.2f, 0.4f}, Vishv::Math::Vector4::Color::Teal()},			//Buttom Right	Back
	//	{{0.4f, 0.2f, 0.4f}, Vishv::Math::Vector4::Color::Navy()},			//Top Right		Back
	//};
	//
	//int vertexSize = 8;
	//
	//int indexBuffer[] = 
	//{
	//		//Front Face
	//		//Top Left Front, Top Right Front, buttom Left Front
	//		0, 3, 1,
	//		3, 2, 1,				//Top Right Front, //Buttom Right Front, //buttom Left Front
	//	
	//		//Right Face
	//		3, 7, 2,				//Top Right Front, //Top Right Back, //Buttom Right Front
	//		7, 6, 2,				//Top Right Back, //Buttom Right Back, //Buttom Right Front
	//
	//		//Left Face
	//		4, 0, 5,
	//		0, 1, 5,
	//
	//		//Buttom Face
	//		7, 5, 1,
	//		7, 1, 2,
	//
	//		//Top Face
	//		0, 4, 3,
	//		3, 4, 7,
	//
	//		//Back Face
	//		7, 4, 5,
	//		7, 5, 6
	//};
	//int indexSize = 36;

	Vishv::Graphics::MeshBuffer mb;
	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	mb.Initialize(mesh);
	ps.Initialize("../../Assets/Shaders/DoTransform.fx");
	vs.Initialize("../../Assets/Shaders/DoTransform.fx", VertexPC::Format);

	/////////////////////////////////////////////////////////////////////////////////////

	ID3D11Buffer *constantBuffer = nullptr;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = 3 * sizeof(Matrix4);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Vishv::Graphics::Camera cam;
	cam.SetPosition({ 0.0f, 0.0f, -10.0f });
	cam.SetDirection({ 0.0f, 0.0f, 0.0f });

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();
		Vishv::Math::Matrix4 transformMatrix(Vishv::Math::Matrix4::Identity());
		Vishv::Math::Matrix4 transformMatrixCube(Vishv::Math::Matrix4::Identity());


		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}
		else if (GetAsyncKeyState(0x57))//w
		{
			transformMatrix.TranslateZ(10.0f);
		}
		else if (GetAsyncKeyState(0x53))//s
		{
			transformMatrix.TranslateZ(-10.0f);
		}
		else if (GetAsyncKeyState(0x41)) //a
		{
			transformMatrix.TranslateX(-10.0f);
		}
		else if (GetAsyncKeyState(0x44)) //d
		{
			transformMatrix.TranslateX(10.0f);
		}
		else if (GetAsyncKeyState(0x51)) //q
		{
			transformMatrix.TranslateY(10.0f);
		}
		else if (GetAsyncKeyState(0x45)) //e
		{
			transformMatrix.TranslateY(-10.0f);
		}
		else if (GetAsyncKeyState(0x5A)) //z
		{
			transformMatrix.RotateX(10.0f);
		}
		else if (GetAsyncKeyState(0x58)) //x
		{
			transformMatrix.RotateY(10.0f);
		}
		//Cube
		else if (GetAsyncKeyState(0x4B)) //K
		{
			transformMatrixCube.RotateY(-10.0f);
		}
		else if (GetAsyncKeyState(0x4C)) //K
		{
			transformMatrixCube.RotateY(10.0f);
		}
		else if (GetAsyncKeyState(0x4F)) //O
		{
			transformMatrixCube.RotateX(-10.0f);
		}
		else if (GetAsyncKeyState(0x50)) //p
		{
			transformMatrixCube.RotateX(10.0f);
		}
		else if (GetAsyncKeyState(0x49)) //i
		{
			transformMatrixCube.Scale(1.0f);
		}
		else if (GetAsyncKeyState(0x4A)) //J
		{
			transformMatrixCube.Scale(-1.0f);
		}
		//	Run Game Logic

		//for (int i = 0; i < vertexSize; ++i)
		//{
		//	vertices[i].position.TransformCoord(transformMatrixCube);
		//}

		GraphicsSystem::Get()->BeginRender();
		cam.ComputeMatricies(1280.0f / 720.0f);

		Matrix4 mat[3];
		mat[0] = transformMatrixCube;
		mat[1] = cam.GetViewMatrix().Transpose();
		mat[2] = cam.GetPerspectiveMatrix().Transpose();

		mb.Bind();
		vs.Bind();
		ps.Bind();
		mb.Draw();

		GraphicsSystem::Get()->EndRender();

	}

	//SafeRelease(vertexShader);
	//SafeRelease(inputLayout);
	//SafeRelease(pixelShader);
	//SafeRelease(vertexBuffer);
	GraphicsSystem::StaticTerminate();
	SafeRelease(constantBuffer);

	myWindow.Terminate();
	return 0;
}


