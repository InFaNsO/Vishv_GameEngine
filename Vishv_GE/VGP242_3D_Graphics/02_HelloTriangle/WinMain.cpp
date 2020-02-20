#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>

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

	//Define the triangle to draw
	Vishv::Graphics::VertexPC vertices[] =
	{
		{ { 0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		{ { 0.5f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		{ {-0.5f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		{ {0.0f, -0.5f, 0.0f}, Vishv::Graphics::Colors::Teal}
	};

	Vishv::Graphics::MeshBuffer mb;
	Vishv::Graphics::PixelShader ps;
	Vishv::Graphics::VertexShader vs;

	MeshPC mesh;
	for(uint32_t i = 0; i < 4; ++i)
		mesh.mVertices.push_back(vertices[i]);

	mb.Initialize(mesh);
	ps.Initialize("../../Assets/Shaders/DoSomething.fx");
	vs.Initialize("../../Assets/Shaders/DoSomething.fx", VertexPC::Format);


	//Old Code

	//Describes what a Vertex Struct is to the GPU
	//const D3D11_INPUT_ELEMENT_DESC elemDescs[] =
	//{
	//	{
	//		"POSITION", 0,
	//		DXGI_FORMAT_R32G32B32_FLOAT,		//Telling the GPU that we have R, G, B as float (32)
	//		0,
	//		D3D11_APPEND_ALIGNED_ELEMENT,
	//		D3D11_INPUT_PER_VERTEX_DATA,
	//		0
	//	},
	//	{
	//		"COLOR", 0,
	//		DXGI_FORMAT_R32G32B32A32_FLOAT,
	//		0,
	//		D3D11_APPEND_ALIGNED_ELEMENT,
	//		D3D11_INPUT_PER_VERTEX_DATA,
	//		0
	//	},
	//};
	//
	//auto device = GraphicsSystem::Get()->GetDevice();
	//
	//ID3D11Buffer* vertexBuffer = nullptr;
	//
	//
	////Allocate memory in the vram for vertex buffer and initialize with out vertex data
	//D3D11_BUFFER_DESC vertexBufferDesc{};
	//
	//vertexBufferDesc.ByteWidth = std::size(vertices) * sizeof(Vert);
	//vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDesc.CPUAccessFlags = 0;
	//vertexBufferDesc.MiscFlags = 0;
	//vertexBufferDesc.StructureByteStride = 0;
	//
	//
	//D3D11_SUBRESOURCE_DATA initData{};
	//initData.pSysMem = vertices;
	//initData.SysMemPitch = 0;
	//initData.SysMemSlicePitch = 0;
	//
	//HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &initData, &vertexBuffer);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to creat vertext buffer");
	//
	////Compile our vertex shader code
	//ID3DBlob* shaderBlob = nullptr;
	//ID3DBlob* errorBlob = nullptr;
	//
	//hr = D3DCompileFromFile(L"../../Assets/Shaders/DoSomething.fx", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &shaderBlob, &errorBlob);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to compile vertex shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	//
	////Create Vertex shader and input layout descriptor
	//ID3D11VertexShader* vertexShader = nullptr;
	//ID3D11InputLayout* inputLayout = nullptr;
	//
	//hr = device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to create vertex shader.");
	//
	//hr = device->CreateInputLayout(elemDescs, std::size(elemDescs), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), &inputLayout);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to create input layout.");
	//
	//
	//SafeRelease(shaderBlob);
	//SafeRelease(errorBlob);
	//
	//
	////Compile pixel shader
	//hr = D3DCompileFromFile(L"../../Assets/Shaders/DoSomething.fx", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &shaderBlob, &errorBlob);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to compile pixel shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	//
	//ID3D11PixelShader* pixelShader = nullptr;
	//hr = device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &pixelShader);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to Create pixel shader.");
	//
	//SafeRelease(shaderBlob);
	//SafeRelease(errorBlob);

	bool done = false;
	while (!done)
	{
		done = myWindow.ProcessMessage();

		if (GetAsyncKeyState(VK_ESCAPE))
		{
			done = true;
		}


		//	Run Game Logic

		GraphicsSystem::Get()->BeginRender();

		mb.Bind();
		vs.Bind();
		ps.Bind();
		mb.Draw();
		//Old Code

		//draw stuff
		//auto context = GraphicsSystem::Get()->GetContext();
		//
		//UINT stride = sizeof(Vert);
		//UINT offset = 0;
		//context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		//
		//context->IASetInputLayout(inputLayout);
		//context->VSSetShader(vertexShader, nullptr, 0);
		//context->PSSetShader(pixelShader, nullptr, 0);
		//
		//
		//context->Draw(std::size(vertices), 0);
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


