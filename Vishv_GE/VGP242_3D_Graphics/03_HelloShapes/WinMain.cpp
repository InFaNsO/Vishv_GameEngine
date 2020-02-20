#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;

//Shape
Vishv::Graphics::VertexPC *Heart;
Vishv::Graphics::VertexPC *TriForce;
Vishv::Graphics::VertexPC *Boat;
Vishv::Graphics::VertexPC *Mountain;
Vishv::Graphics::VertexPC *Tree;

Vishv::Graphics::MeshBuffer mb;

void SetHeart()
{
	Heart = new Vishv::Graphics::VertexPC[9]{


		//Main Triangle
		{ { 0.3f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Right
		{ { 0.0f, -0.3f, 0.0f }, Vishv::Math::Vector4::Color::Red() },		//Buttom
		{ { -0.3f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Left

		{ {-0.15f, 0.5f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Top Left
		{ {0.0f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() },			//Middle
		{ { -0.3f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Left

		{ {0.15f, 0.5f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Top Right
		{ { 0.3f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() },		//Right
		{ {0.0f, 0.3f, 0.0f}, Vishv::Math::Vector4::Color::Red() }			//Middle
	};

	mb.Initialize(9, sizeof(Vishv::Graphics::VertexPC), Heart);
}

void SetTriforce()
{
	TriForce = new Vishv::Graphics::VertexPC[9]{

		//Left Triangle
		{ {-0.2f, 0.0f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Top
		{ {0.0f, -0.4f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Right
		{ {-0.4f, -0.4f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Left
		//Right Triangle
		{ {0.2f, 0.0f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Top
		{ {0.4f, -0.4f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Right
		{ {0.0f, -0.4f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Left
		//Top Triangle
		{ {0.0f, 0.4f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Top
		{ {0.2f, 0.0f, 0.0f}, Vishv::Math::Vector4::Color::Gold() },		//Right
		{ {-0.2f, 0.0f, 0.0f}, Vishv::Math::Vector4::Color::Gold() }		//Left
	};
	mb.Initialize(9, sizeof(Vishv::Graphics::VertexPC), TriForce);
}

void SetBoat()
{
	Boat = new Vishv::Graphics::VertexPC[27]{


		//Left Body		
		//Left Triangle
		{ {-0.48f, 0.16f, 0.0f},	{0.929f, 0.64f, 0.73f} },		//Left
		{ {0.24f, 0.08f, 0.0f}	,	{0.929f, 0.64f, 0.73f} },		//Right
		{ {-0.28f, 0.16f, 0.0f},	{0.929f, 0.64f, 0.73f} },		//Buttom
		//Right Triangle
		{ {0.24f, 0.08f, 0.0f}	,	{0.91f, 0.546f, 0.66f} },		//Left
		{ {0.0f, 0.0f, 0.0f}	,	{0.91f, 0.546f, 0.66f} },		//Right
		{ {-0.28f, 0.16f, 0.0f},	{0.91f, 0.546f, 0.66f} },		//Buttom

		//Center Body
		//Left Triangle
		{ {0.0f, 0.0f, 0.0f}	,	{0.957f, 0.808f, 0.851f} },		//Top
		{ {0.0f, 0.16f, 0.0f}	,	{0.957f, 0.808f, 0.851f} },		//Right
		{ {-0.28f, 0.16f, 0.0f},	{0.957f, 0.808f, 0.851f} },		//Left
		//Right Triangle
		{ {0.0f, 0.0f, 0.0f}	,	{0.91f, 0.546f, 0.66f} },		//Top
		{ {0.28f, 0.16f, 0.0f},	{0.91f, 0.546f, 0.66f} },		//Right
		{ {0.0f, 0.16f, 0.0f}	,	{0.91f, 0.546f, 0.66f} },		//Left

		//Right Body
		{ {0.0f, 0.0f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Left
		{ {0.48f, 0.12f, 0.0f},	{0.804f, 0.074f, 0.289f} },		//Right
		{ {0.28f, 0.16f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Buttom

		//Left Sail
		//Left Triangle
		{ {0.0f, 0.24f, 0.0f}	,	{0.957f, 0.808f, 0.851f} },		//Top
		{ {-0.02f, -0.02f, 0.0f},	{0.957f, 0.808f, 0.851f} },		//Right
		{ {-0.16f, 0.042f, 0.0f},	{0.957f, 0.808f, 0.851f} },		//Left
		//Right Triangle
		{ {0.0f, 0.24f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Top
		{ {0.0f, 0.0f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Right
		{ {0.02f, 0.02f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Left

		//Right Sail
		//Left Triangle
		{ {0.0f, 0.24f, 0.0f}	,	{0.929f, 0.679f, 0.734f} },		//Top
		{ {0.02f, 0.02f, 0.0f}	,	{0.929f, 0.679f, 0.734f} },		//Right
		{ {0.0f, 0.0f, 0.0f}	,	{0.929f, 0.679f, 0.734f} },		//Left
		//Right Triangle
		{ {0.0f, 0.24f, 0.0f}	,	{0.804f, 0.074f, 0.289f} },		//Top
		{ {0.16f, 0.042f, 0.0f},	{0.804f, 0.074f, 0.289f} },		//Right
		{ {0.02f, 0.02f, 0.0f}	,	{0.804f, 0.074f, 0.289f} }		//Left
	};
	mb.Initialize(27, sizeof(Vishv::Graphics::VertexPC), Boat);
}

void SetMountain()
{
	Mountain = new Vishv::Graphics::VertexPC[21]{

		//MainTriangle
		{ {0.0f, 0.8f, 0.5f}, {0.0429f, 0.5312f, 0.4687f, 1.0f} },			//Top
		{ {0.8f, -0.3f, 0.5f}, {0.0429f, 0.5312f, 0.4687f, 1.0f}},		//Right
		{ {-0.8f, -0.3f, 0.5f},{0.0429f, 0.5312f, 0.4687f, 1.0f}},		//Left

		//Aqua

		// top triangle Left
		{ {0.0f, 0.8f, 0.0f},		Vishv::Math::Vector4::Color::Aqua() },		//Top
		{ {0.0f, 0.4f, 0.0f},		Vishv::Math::Vector4::Color::Aqua() },		//Right
		{ {-0.3f, 0.4f, 0.0f},		Vishv::Math::Vector4::Color::Aqua() },		//Left

		// triangle Left 1
		{ {-0.3f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Top
		{ {-0.2f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Right
		{ {-0.44f, 0.2f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Left

		// triangle Left 2
		{ {-0.2f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Top
		 { {0.0f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Right
		 { {0.0f, 0.2f, 0.0f},	Vishv::Math::Vector4::Color::Aqua() },			//Left

		//Navy

		// Top triangle Right 
		{ {0.0f, 0.8f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },		//Top
		{ {0.3f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },		//Right
		{ {0.0f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },		//Left

		// triangle Right 1
		{ {0.2f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },			//Top
		{ {0.3f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },			//Righ
		{ {0.44f, 0.2f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },			//Left

		// triangle Right 2
		{ {0.0f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },			//Top
		{ {0.2f, 0.4f, 0.0f},	Vishv::Math::Vector4::Color::Navy() },			//Righ
		{ {0.0f, 0.2f, 0.0f},	Vishv::Math::Vector4::Color::Navy() }			//Left
	};

	mb.Initialize(21, sizeof(Vishv::Graphics::VertexPC), Mountain);
}

void SetTree()
{
	Tree = new Vishv::Graphics::VertexPC[5];
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//Make the window
	Vishv::Core::Window myWindow;
	myWindow.Initialize(hInstance, "Hello Triangle", 1280, 720);

	//initialize graphics system
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);

	//Define the triangle to draw


	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	
	ps.Initialize("../../Assets/Shaders/DoSomething.fx");
	vs.Initialize("../../Assets/Shaders/DoSomething.fx", VertexPC::Format);



	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}
		else if (GetAsyncKeyState(0x42))		//Pressed B
		{
			//draw boat
			SetBoat();
		}
		else if (GetAsyncKeyState(0x48))		//Pressed H
		{
			//Draw Heart
			SetHeart();
		}
		else if (GetAsyncKeyState(0x54))		//Pressed T
		{
			//Draw TriForce
			SetTriforce();
		}
		else if (GetAsyncKeyState(0x4D))		//Pressed M
		{
			//Draw TriForce
			SetMountain();
		}
		//	Run Game Logic

		GraphicsSystem::Get()->BeginRender();

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

	myWindow.Terminate();
	return 0;
}
