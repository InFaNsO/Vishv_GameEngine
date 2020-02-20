#ifndef INCLUDED_VISHV_GRAPHICS_EFFECT_H
#define INCLUDED_VISHV_GRAPHICS_EFFECT_H

#include "VertexTypes.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"
#include "EffectsConstantBuffer.h"

namespace Vishv::Graphics
{
	struct Effect
	{
		void Initialize(std::filesystem::path path, uint32_t shaderFormat, uint32_t bufferFormat, uint32_t vertexType)
		{
			mBufferData.SetBufferTypes(bufferFormat);
			mConstantBuffer.Intialize(bufferFormat, shaderFormat);

			mVertexShader.Initialize(path, vertexType);
			mPixelShader.Initialize(path);

			if (shaderFormat & Vishv::Graphics::ShaderType::EF_GEOMETRY)
				mGeometryShader.Initialize(path);
		}
		
		void Terminate()
		{
			if (mConstantBuffer.GetFormat() & ShaderType::EF_GEOMETRY)
				mGeometryShader.Terminate();
			mVertexShader.Terminate();
			mPixelShader.Terminate();

			mConstantBuffer.Terminate();
			mBufferData.Terminate();
		}

		void BindEffects()
		{
			mVertexShader.Bind();
			mPixelShader.Bind();

			if (mConstantBuffer.GetFormat() & ShaderType::EF_GEOMETRY)
				mGeometryShader.Bind();
		}

		EffectsConstantBuffer mConstantBuffer;
		EffectBufferData mBufferData;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		GeometryShader mGeometryShader;

		//uint32_t VertexType;
		//uint32_t format;
	};
}


#endif // !INCLUDED_VISHV_GRAPHICS_EFFECT_H


