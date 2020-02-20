#include "Precompiled.h"
#include "GeometryShader.h"
#include "D3DUtil.h"
#include "VertexTypes.h"

using namespace Vishv;
using namespace Vishv::Graphics;

bool Vishv::Graphics::GeometryShader::Initialize(std::string shaderName)
{
	std::filesystem::path p = shaderName;
	return Initialize(p);
}
bool Vishv::Graphics::GeometryShader::Initialize(std::filesystem::path shaderPath)
{
	HRESULT hr;

	//Compile our vertex shader code
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;


	hr = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "GS", "gs_5_0", 0, 0, &shaderBlob, &errorBlob);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to compile geometry shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	if (SUCCEEDED(hr))
	{
		LOG("Failed to compile geometry shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
		SafeRelease(shaderBlob);
		SafeRelease(errorBlob);
		return false;
	}

	hr = GetDevice()->CreateGeometryShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &mGeometryShader);
	//VISHVASSERT(SUCCEEDED(hr), "Failed to create geometry shader.");
	if (SUCCEEDED(hr))
	{
		LOG("Failed to Create geometry shader.");
		SafeRelease(shaderBlob);
		SafeRelease(errorBlob);
		return false;
	}

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	return true;
}

std::wstring Vishv::Graphics::GeometryShader::ConvertString(std::string & s)
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

void Vishv::Graphics::GeometryShader::Bind()
{
	GetContext()->GSSetShader(mGeometryShader, nullptr, 0);
}

void Vishv::Graphics::GeometryShader::UnBind()
{
	GetContext()->GSSetShader(nullptr, nullptr, 0);
}

Vishv::Graphics::GeometryShader::~GeometryShader()
{
	VISHVASSERT(!mGeometryShader, "[Vishv::Graphics::GeometryShader] Didn't call terminate for Geometry Shader.");
}

void Vishv::Graphics::GeometryShader::Terminate()
{
	SafeRelease(mGeometryShader);
}
