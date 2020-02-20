#include "Precompiled.h"
#include "VertexShader.h"
#include "D3DUtil.h"
#include "VertexTypes.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> GetVertexLayout(uint32_t vertexFormat)
	{
		std::vector< D3D11_INPUT_ELEMENT_DESC> desc;
		if (vertexFormat & VE_Position)
		{
			desc.push_back({ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_Normal)
		{
			desc.push_back({ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_Tangent)
		{
			desc.push_back({ "TANGENT",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_Color)
		{
			desc.push_back({ "Color",			0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_Texcoord)
		{
			desc.push_back({"TEXCOORD",			0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0});
		}
		if (vertexFormat & VE_Blendindex)
		{
			desc.push_back({ "BLENDINDICES",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexFormat & VE_BlendWeights)
		{
			desc.push_back({ "BLENDWEIGHTS",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		return desc;
	}
}

bool Vishv::Graphics::VertexShader::Initialize(std::filesystem::path shaderPath, uint32_t vertexFormat)
{
	//Describes what a Vertex Struct is to the GPU
	auto elemDescs = GetVertexLayout(vertexFormat);

	HRESULT hr;

	//Compile our vertex shader code
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	hr = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "VS", "vs_5_0", 0, 0, &shaderBlob, &errorBlob);
	VISHVASSERT(SUCCEEDED(hr), "Failed to compile vertex shader. Error: %s", (const char*)errorBlob->GetBufferPointer());

	hr = GetDevice()->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &mVertexShader);
	VISHVASSERT(SUCCEEDED(hr), "Failed to create vertex shader.");

	hr = GetDevice()->CreateInputLayout
	(elemDescs.data(), (UINT)elemDescs.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);

	VISHVASSERT(SUCCEEDED(hr), "Failed to create input layout.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	return true;
}

std::wstring Vishv::Graphics::VertexShader::ConvertString(std::string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


void Vishv::Graphics::VertexShader::Bind()
{
	GetContext()->IASetInputLayout(mInputLayout);
	GetContext()->VSSetShader(mVertexShader, nullptr, 0);
}

Vishv::Graphics::VertexShader::~VertexShader()
{
	VISHVASSERT(!mVertexShader || !mInputLayout, "[Vishv::Graphics::VertexShader] Didn't call terminate for vertex shader.");
}

void Vishv::Graphics::VertexShader::Terminate()
{
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout);
}