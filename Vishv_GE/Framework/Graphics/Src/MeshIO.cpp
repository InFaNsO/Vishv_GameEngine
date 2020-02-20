#include "Precompiled.h"
#include "Texture.h"
#include "Model.h"
#include "MeshIO.h"
#include "VertexTypes.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	void MakeString(uint32_t format, VertexALL& v, std::string& txt)
	{
		txt = "";
		//do position -> normal -> tangent -> UV

		if (format & VE_Position)
			txt += v.position.ToString() + " ";
		if (format & VE_Normal)
			txt += v.normal.ToString() + " ";
		if (format & VE_Tangent)
			txt += v.tangent.ToString() + " ";
		if (format & VE_Color)
			txt += v.color.ToString() + " ";
		if (format & VE_Texcoord)
			txt += v.texCoord.ToString() + " ";
		if (format & VE_Blendindex)
			txt += std::to_string(v.boneIndecies[0]) + " " + std::to_string(v.boneIndecies[1]) + " " + std::to_string(v.boneIndecies[2]) + " " + std::to_string(v.boneIndecies[3]) + " ";
		if (format & VE_BlendWeights)
			txt += std::to_string(v.boneWeights[0]) + " " + std::to_string(v.boneWeights[1]) + " " + std::to_string(v.boneWeights[2]) + " " + std::to_string(v.boneWeights[3]) + " ";

		txt += "\n";
	}
}

bool MeshIO::SaveMesh(ModelImport & mesh, std::string name)
{
	std::filesystem::path filePath = rootPath / name;
	filePath /= name + "_Mesh.vmesh";

	return SaveMesh(mesh, filePath);
}

bool MeshIO::SaveMesh(ModelImport& model, std::filesystem::path path)
{
	std::fstream file;
	file.open(path, std::ios::out | std::ios::app);
	file.close();
	file.open(path);
	if (!file.is_open())
		return false;
;
	//file.clear();

	file << "MeshFormat: " << model.meshFormat << std::endl;
	file << "NumberMeshes: " << model.mMeshes.size() << std::endl;

	for (size_t index = 0; index < model.mMeshes.size(); ++index)
	{
		file << "\nMeshID: " << index << std::endl;
		file << "MaterialIndex: " << model.mMeshes[index].mIndex << std::endl;
		file << "VertexCount: " << model.mMeshes[index].mMesh.mVertices.size() << std::endl;
		file << "IndexCount: " << model.mMeshes[index].mMesh.mIndices.size() << std::endl;

		std::string txt;
		for (size_t i = 0; i < model.mMeshes[index].mMesh.mVertices.size(); ++i)
		{
			MakeString(model.meshFormat, model.mMeshes[index].mMesh.mVertices[i], txt);
			file << txt;
		}
		file << "\n";

		for (size_t i = 0; i < model.mMeshes[index].mMesh.mIndices.size(); ++i)
		{
			file << model.mMeshes[index].mMesh.mIndices[i] << " ";
		}
	}

	file << "\nNumberMaterials: " << model.mMaterials.size() << "\n";

	for (size_t i = 0; i < model.mMaterials.size(); ++i)
	{
		std::string txt = "";
		txt += "\nMaterialID: " + std::to_string(i) + "\n";
		file << txt;

		txt = std::to_string((int)Graphics::Texture::Type::Bump) + " " + model.mMaterials[i].bumpName + "\n";
		file << txt;
		txt = std::to_string((int)Graphics::Texture::Type::Diffuse) + " " + model.mMaterials[i].diffuseName + "\n";
		file << txt;
		txt = std::to_string((int)Graphics::Texture::Type::Normal) + " " + model.mMaterials[i].normalName + "\n";
		file << txt;
		txt = std::to_string((int)Graphics::Texture::Type::Specular) + " " + model.mMaterials[i].specularName + "\n";
		file << txt;
	}

	file.close();
	return true;
}

bool MeshIO::LoadMeshGeneral(std::filesystem::path fileName)
{
	isLoaded = false;
	std::fstream file;
	auto p = rootPath / fileName;
	file.open(p);

	if (!file.is_open())
		return isLoaded;

	int numVertex, numIndex, numMesh, id;
	uint32_t vertexType;
	std::string holder;

	file >> holder >> vertexType;
	//if(vertexType != Vertex::Format)
	//	return false;

	load.meshFormat = vertexType;

	file >> holder >> numMesh;

	load.mMeshes.reserve(numMesh);


	for (int i = 0; i < numMesh; ++i)
	{
		int index = -1;
		file >> holder >> id;
		file >> holder >> index;
		file >> holder >> numVertex;
		file >> holder >> numIndex;


		ModelImport::MeshData<MeshImport> data;

		data.mIndex = index;
		data.mMesh.mIndices.reserve(numIndex);
		data.mMesh.mVertices.reserve(numVertex);

		//read the vertices
		VertexALL v;
		for (int i = 0; i < numVertex; ++i)
		{
			//do position -> normal -> tangent -> UV

			if (vertexType & VE_Position)
				file >> v.position.x >> v.position.y >> v.position.z;
			if (vertexType & VE_Normal)
				file >> v.normal.x >> v.normal.y >> v.normal.z;
			if (vertexType & VE_Tangent)
				file >> v.tangent.x >> v.tangent.y >> v.tangent.z;
			if (vertexType & VE_Color)
				file >> v.color.x >> v.color.y >> v.color.z;
			if (vertexType & VE_Texcoord)
				file >> v.texCoord.x >> v.texCoord.y;
			if (vertexType & VE_Blendindex)
				file >> v.boneIndecies[0] >> v.boneIndecies[1] >> v.boneIndecies[2] >> v.boneIndecies[3];
			if (vertexType & VE_BlendWeights)
				file >>v.boneWeights[0] >> v.boneWeights[1]>> v.boneWeights[2] >> v.boneWeights[3];
			data.mMesh.mVertices.emplace_back(v);
		}

		int ind;
		for (int i = 0; i < numIndex; ++i)
		{
			file >> ind;
			data.mMesh.mIndices.emplace_back(ind);
		}

		load.mMeshes.emplace_back(data);
	}

	int materialCount = 0;
	file >> holder >> materialCount;

	if (materialCount != 0)
	{
		load.mMaterials.reserve(materialCount);
		for (int i = 0; i < materialCount; ++i)
		{
			file >> holder >> id;
			
			int type;

			ModelImport::MaterialData data;

			file >> type >> data.bumpName;
			file >> type >> data.diffuseName;
			file >> type >> data.normalName;
			file >> type >> data.specularName;

			load.mMaterials.emplace_back(data);
		}
	}

	file.close();
	isLoaded = true;
	return isLoaded;
}

bool Vishv::Graphics::MeshIO::GetModel(Model & model)
{
	//VISHVASSERT(load.meshFormat == 0, "[Model Import] Error didnt load the model first");
	//VISHVASSERT(load.meshFormat != BoneVertex::Format, "[Model Import] Error wrong type of model to load");

	model.mMeshes.resize(load.mMeshes.size());
	for (uint32_t i = 0; i < load.mMeshes.size(); ++i)
	{
		model.mMeshes[i].mIndex = load.mMeshes[i].mIndex;
		BoneVertex v;
		for (uint32_t vertexI = 0; vertexI < load.mMeshes[i].mMesh.mVertices.size(); ++vertexI)
		{
			//copy all the vertices
			v.position = load.mMeshes[i].mMesh.mVertices[vertexI].position;
			v.normal = load.mMeshes[i].mMesh.mVertices[vertexI].normal;
			v.tangent = load.mMeshes[i].mMesh.mVertices[vertexI].tangent;
			v.texCoord = load.mMeshes[i].mMesh.mVertices[vertexI].texCoord;

			for (uint32_t boneIndex = 0; boneIndex < 4; ++boneIndex)
			{
				v.boneIndecies[boneIndex] = load.mMeshes[i].mMesh.mVertices[vertexI].boneIndecies[boneIndex];
				v.boneWeights[boneIndex] = load.mMeshes[i].mMesh.mVertices[vertexI].boneWeights[boneIndex];
			}
			model.mMeshes[i].mMesh.mVertices.emplace_back(v);
		}
		model.mMeshes[i].mMesh.mIndices.reserve(load.mMeshes[i].mMesh.mIndices.size());
		for (uint32_t indexI = 0; indexI < load.mMeshes[i].mMesh.mIndices.size(); ++indexI)
		{
			model.mMeshes[i].mMesh.mIndices.emplace_back(load.mMeshes[i].mMesh.mIndices[indexI]);
		}
	}
	model.mMaterials.reserve(load.mMaterials.size());
	for (uint32_t materialIndex = 0; materialIndex < load.mMaterials.size(); ++materialIndex)
	{
		Model::MaterialData mMatData;
		mMatData.diffuseName = load.mMaterials[materialIndex].diffuseName;
		mMatData.bumpName = load.mMaterials[materialIndex].bumpName;
		mMatData.normalName = load.mMaterials[materialIndex].normalName;
		mMatData.specularName= load.mMaterials[materialIndex].specularName;

		model.mMaterials.emplace_back(mMatData);
	}
	return true;
}

bool Vishv::Graphics::MeshIO::GetModel(ModelPNX & model)
{
	VISHVASSERT(load.meshFormat == 0, "[Model Import] Error didnt load the model first");
	VISHVASSERT(load.meshFormat != BoneVertex::Format, "[Model Import] Error wrong type of model to load");

	model.mMeshes.reserve(load.mMeshes.size());
	for (uint32_t i = 0; i < load.mMeshes.size(); ++i)
	{
		model.mMeshes[i].mIndex = load.mMeshes[i].mIndex;
		VertexPNX v;
		for (uint32_t vertexI = 0; vertexI < load.mMeshes[i].mMesh.mVertices.size(); ++vertexI)
		{
			//copy all the vertices
			v.position = load.mMeshes[i].mMesh.mVertices[vertexI].position;
			v.normal = load.mMeshes[i].mMesh.mVertices[vertexI].normal;
			v.texCoord = load.mMeshes[i].mMesh.mVertices[vertexI].texCoord;
			
			model.mMeshes[i].mMesh.mVertices.emplace_back(v);
		}
		model.mMeshes[i].mMesh.mIndices.reserve(load.mMeshes[i].mMesh.mIndices.size());
		for (uint32_t indexI = 0; indexI < load.mMeshes[i].mMesh.mIndices.size(); ++indexI)
		{
			model.mMeshes[i].mMesh.mIndices.emplace_back(load.mMeshes[i].mMesh.mIndices[indexI]);
		}
	}
	model.mMaterials.reserve(load.mMaterials.size());
	for (uint32_t materialIndex = 0; materialIndex < load.mMaterials.size(); ++materialIndex)
	{
		ModelPNX::MaterialData mMatData;
		mMatData.diffuseName = load.mMaterials[materialIndex].diffuseName;
		mMatData.bumpName = load.mMaterials[materialIndex].bumpName;
		mMatData.normalName = load.mMaterials[materialIndex].normalName;
		mMatData.specularName = load.mMaterials[materialIndex].specularName;

		model.mMaterials.emplace_back(mMatData);
	}
	return true;
}

