#ifndef INCLUDED_VISHV_GRAPHICS_MODEL
#define INCLUDED_VISHV_GRAPHICS_MODEL

#include "Mesh.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Texture.h"
#include "ConstantBuffer.h"
#include "Camera.h"

namespace Vishv::Graphics {

	template <class MESH>
	class ModelBase
	{
	public:
		template <class MESHTYPE>
		struct MeshData
		{
			MESHTYPE mMesh;
			int mIndex = -1;
			MeshBuffer mBuffer;
		};

		struct MaterialData
		{
			std::string diffuseName = "empty";
			std::string bumpName = "empty";
			std::string normalName = "empty";
			std::string specularName = "empty";

			TextureID diffuseID;
			TextureID bumpID;
			TextureID normalID;
			TextureID specularID;
		};

		std::vector<MaterialData> mMaterials;
		std::vector<MeshData<MESH>> mMeshes;

		uint32_t meshFormat = 0;

		void Render()
		{
			for (uint32_t i = 0; i < mMeshes.size(); ++i)
			{
				Vishv::Graphics::TextureManager::Get()->GetTexture(mMaterials[mMeshes[i].mIndex].diffuseID)->BindPS(0);
				Vishv::Graphics::TextureManager::Get()->GetTexture(mMaterials[mMeshes[i].mIndex].specularID)->BindPS(1);
				Vishv::Graphics::TextureManager::Get()->GetTexture(mMaterials[mMeshes[i].mIndex].bumpID)->BindVS(2);
				Vishv::Graphics::TextureManager::Get()->GetTexture(mMaterials[mMeshes[i].mIndex].normalID)->BindPS(3);

				Vishv::Graphics::SamplerManager::Get()->GetSampler("LinearWrap")->BindPS(0);

				mMeshes[i].mBuffer.Render();
			}
		}
	};

	using ModelImport = ModelBase<MeshImport>;		//used only for import 
	using Model = ModelBase<BoneMesh>;			//Main model format
	using ModelPNX = ModelBase<MeshPNX>;		//Model with normal and uv
}

#endif // !INCLUDED_VISHV_GRAPHICS_MODEL


