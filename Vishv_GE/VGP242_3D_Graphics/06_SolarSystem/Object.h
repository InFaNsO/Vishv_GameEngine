#pragma once
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/VishvMath.h>

using namespace Vishv::Core;
using namespace Vishv::Graphics;
using namespace Vishv::Math;

struct ObjectTexture
{
	MeshPX meshTexture;

	Vishv::Math::Matrix4 tranformation{ Vishv::Math::Matrix4::Identity() };

	Vishv::Graphics::ConstantBuffer cb;
	Vishv::Graphics::MeshBuffer		mb;
	Vishv::Graphics::PixelShader	ps;
	Vishv::Graphics::VertexShader	vs;
	Vishv::Graphics::Texture		tx;
	Vishv::Graphics::Sampler		sm;

	void Initialize(const wchar_t* textureName, const char* shaderName = "../../Assets/Shaders/Texturing.fx")
	{
		tx.Initialize(textureName);
		sm.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
		cb.Initialize();
		mb.Initialize(meshTexture);

		std::filesystem::path p = shaderName;

		ps.Initialize(p);
		vs.Initialize(p, VertexPX::Format);
	}

	void Update(Matrix4 mat[])
	{
		cb.Bind(mat);
		mb.Bind();
		tx.BindPS();
		sm.BindPS();
		vs.Bind();
		ps.Bind();
		mb.Render();
	}

	void Terminate()
	{
		vs.Terminate();
		cb.Terminate();
		mb.Terminate();
		ps.Terminate();
		sm.Terminate();
		tx.Terminate();
	}
};