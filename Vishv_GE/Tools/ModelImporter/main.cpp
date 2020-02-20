#include <Vishv/Inc/Vishv.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Vishv::Graphics;

std::string modelName = "lambo";
std::filesystem::path root = L"../../Assets/Models";

using BoneVector = std::vector<std::unique_ptr<Vishv::Graphics::Bone>>;
using BoneIndexLookup = std::map<std::string, int>;	//used to look up bones by name

Vishv::Math::Matrix4 Convert(const aiMatrix4x4& matrix)
{
	auto mat = reinterpret_cast<const Vishv::Math::Matrix4*>(&matrix);
	return Vishv::Math::Matrix4::Transpose(mat);//.Transpose();
}
Vishv::Math::Quaternion Convert(const aiQuaternion& quaternion)
{
	Vishv::Math::Quaternion q;
	q.x = quaternion.x;
	q.y = quaternion.y;
	q.z = quaternion.z;
	q.w = quaternion.w;

	return q;
}
Vishv::Math::Vector3 Convert(const aiVector3D& vec)
{
	Vishv::Math::Vector3 v;
	v.x = vec.x;
	v.y = vec.y;
	v.z = vec.z;
	return v;
}


//check if the bone exists then get index else add to skeleton then return index
//the aiBone has to have name
int TryAddBoneIndex(const aiBone* inputBone, Vishv::Graphics::Skeleton& skeleton, BoneIndexLookup& lookup)
{
	std::string name = inputBone->mName.C_Str();
	VISHVASSERT(!name.empty(), "[ModelImporter] Error: input bone has no name");

	auto iter = lookup.find(name);
	if (iter != lookup.end())
		return iter->second;

	//create the bone
	auto& nBone = skeleton.bones.emplace_back(std::make_unique<Vishv::Graphics::Bone>());
	nBone->name = std::move(name);
	nBone->index = static_cast<int>(skeleton.bones.size()) - 1;
	nBone->offsetTransform = Convert(inputBone->mOffsetMatrix);

	//cache bone index
	lookup.emplace(nBone->name, nBone->index);
	return nBone->index;
}

//recurcively walk the ai skeleton and add/link bones to our skeleton as we find them
Vishv::Graphics::Bone* BuildSkeleton(const aiNode& sceneNode, Vishv::Graphics::Bone* parent, Vishv::Graphics::Skeleton& skeleton, BoneIndexLookup& lookup)
{
	Bone* bone = nullptr;
	std::string name = sceneNode.mName.C_Str();
	auto iter = lookup.find(name);
	if (iter != lookup.end())
	{
		bone = skeleton.bones[iter->second].get();
	}
	else
	{
		bone = skeleton.bones.emplace_back(std::make_unique<Bone>()).get();
		bone->index = static_cast<int>(skeleton.bones.size()) - 1;
		bone->offsetTransform = Vishv::Math::Matrix4::Identity();// Convert(sceneNode.mTransformation);
		if (name.empty())
			bone->name = "NoName" + std::to_string(bone->index);
		else
			bone->name = std::move(name);

		lookup.emplace(bone->name, bone->index);
	}
	bone->parent = parent;
	bone->parentId = parent ? parent->index : -1;
	bone->toParentTransform = Convert(sceneNode.mTransformation);

	bone->children.reserve(sceneNode.mNumChildren);
	for (uint32_t i = 0; i < sceneNode.mNumChildren; ++i)
	{
		Bone* child = BuildSkeleton(*sceneNode.mChildren[i], bone, skeleton, lookup);
		bone->children.push_back(child);
		bone->childIndicies.push_back(child->index);
	}
	return bone;
}

struct Arguments
{
	const char* InputFileName = nullptr;
	const char* OutputFileName = nullptr;
};

void PrintUsage()
{
	//provide usage
	printf(
		"==Model_Importer help ==\n"
		"\n"
		"Usage: \n"
		"	ModelImporter.exe [Options] <InputFile> <OutputFile>\n"
		"\n"
		"Options: \n"
		"\n"
		"	<none>\n"
		"\n"
	);
}

//void MakeString(Vishv::Graphics::Vertex& v, std::string& txt)
//{
//	txt = "";
//	//do position -> normal -> tangent -> UV
//
//	txt += v.position.ToString() + " ";
//	txt += v.normal.ToString() + " ";
//	txt += v.tangent.ToString() + " ";
//	txt += v.texCoord.ToString() + "\n";
//}

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	//we need 3 arguments
	if (argc < 3)
		return std::nullopt;

	Arguments args;
	args.OutputFileName = argv[argc - 1];
	args.InputFileName = argv[argc - 2];
	return args;
}

void GetTexture(std::string &data, const aiScene* scene, std::string name, int iteration, aiString texturePath, Arguments args)
{
	const aiTexture* embedded = scene->GetEmbeddedTexture(texturePath.data);
	if (embedded != nullptr)
	{
		std::string filename = args.InputFileName;
		filename.erase(0, filename.rfind("\\") + 1);
		if (filename.size() == 0)
			filename = args.InputFileName;
		filename.erase(filename.length() - 4);			//to remove the extention
		filename += name;
		filename += std::to_string(iteration);

		if (embedded->CheckFormat("jpg"))
			filename += ".jpg";
		else if (embedded->CheckFormat("png"))
			filename += ".png";
		else
			printf("Wrong file format.");		//END

		printf("Extracting embedded texture %s ...\n", filename.c_str());

		std::string fullFileName = args.OutputFileName;
		fullFileName = fullFileName.substr(0, fullFileName.rfind('\\') + 1);
		fullFileName += filename;

		FILE* file = nullptr;
		fopen_s(&file, fullFileName.c_str(), "wb");
		size_t written = fwrite(embedded->pcData, 1, embedded->mWidth, file);
		VISHVASSERT(written == embedded->mWidth, "[Model Impporter] Error : failed to extract embedded texture");
		fclose(file);

		printf("Adding Texture %s...\n", filename.c_str());
		data = fullFileName;
	}
	else
	{
		std::filesystem::path filePath = texturePath.C_Str();
		std::string name = filePath.filename().u8string();
		printf("Adding Texture %s...\n", filePath.filename().generic_string().c_str() );
		std::filesystem::path root = args.OutputFileName;
		root.remove_filename();
		data = root.string() + name;
	}
}

int main(int argc, char* argv[])
{
	auto argsOpt = ParseArgs(argc, argv);
	
	if (!argsOpt.has_value())
	{
		//PrintUsage();
		return -1;

		//argsOpt.value().InputFileName = "../../";
	}
	auto& args = argsOpt.value();


	//Create an instance of the importer class to do parcing for us
	Assimp::Importer importer;
	//const aiMesh* scene = importer.ReadFile(argsOpt->InputFileName, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Quality);
	const aiScene* scene = importer.ReadFile(argsOpt->InputFileName, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Quality);
	if (scene == nullptr)
	{
		printf("\nError: %s\n", importer.GetErrorString());
		return -1;
	}
	
	/*
	What scene is-
		-mesh[][][][]
		-material[][][][][][]
		-animation[][][][]
		-Root Node
			-more nodes
				-child Nodes

	*/

	ModelImport model;
	Skeleton skeleton;
	BoneIndexLookup boneIndexLookUp;
	std::vector<std::unique_ptr<AnimationClip>> animationsClips;

	//look for mesh data
	if (scene->HasMeshes())
	{
		printf("\nReading mesh data...\n");
		uint32_t numMeshes = scene->mNumMeshes;
		uint32_t numMaterials = scene->mNumMaterials;

		uint32_t forma = VE_Position | VE_Normal | VE_Tangent | VE_Texcoord;

		model.mMeshes.reserve(numMeshes);
		bool setBoneVar = false;

		for (uint32_t index = 0; index < numMeshes; ++index)
		{
			ModelBase<MeshImport>::MeshData<MeshImport> info;

			const aiMesh* inputMesh = scene->mMeshes[index];
			uint32_t numVertices = inputMesh->mNumVertices;
			uint32_t numIndex = numVertices * 3;

			info.mIndex = scene->mMeshes[index]->mMaterialIndex;

			info.mMesh.mVertices.reserve(numVertices);
			info.mMesh.mIndices.reserve(numIndex);

			//Get the data
			const aiVector3D* positions = inputMesh->mVertices;
			const aiVector3D* normals = inputMesh->mNormals;
			const aiVector3D* tangents = inputMesh->mTangents;
			const aiVector3D* uvs = inputMesh->mTextureCoords[0];

			Vishv::Graphics::VertexALL v;
			for (uint32_t i = 0; i < numVertices; ++i)
			{
				v.position = { positions[i].x, positions[i].y, positions[i].z };
				v.normal = { normals[i].x, normals[i].y, normals[i].z };
				//v.tangent = tangents == nullptr ? {0.0f,0.0f,0.0f} : { tangents[i].x, tangents[i].y, tangents[i].z };
				v.texCoord.x = uvs[i].x;
				v.texCoord.y = uvs[i].y;

				info.mMesh.mVertices.emplace_back(v);
			}

			//get indeces
			const aiFace* faces = inputMesh->mFaces;
			for (uint32_t i = 0; i < inputMesh->mNumFaces; ++i)
			{
				for (int j = 0; j < 3; ++j)
					info.mMesh.mIndices.emplace_back(faces[i].mIndices[j]);
			}

			if (inputMesh->HasBones())
			{
				printf("\nReading bones...\n");

				if (!setBoneVar)
				{
					forma += VE_Blendindex | VE_BlendWeights;
					setBoneVar = true;
				}
				//track how many weights have we added to each vertex so far
				std::vector<int> numWeigths(info.mMesh.mVertices.size(), 0);
				for (uint32_t meshBoneIndex = 0; meshBoneIndex < inputMesh->mNumBones; ++meshBoneIndex)
				{
					aiBone* inputBone = inputMesh->mBones[meshBoneIndex];
					int boneIndex = TryAddBoneIndex(inputBone, skeleton, boneIndexLookUp);

					for (uint32_t weightIndex = 0; weightIndex < inputBone->mNumWeights; ++weightIndex)
					{
						const aiVertexWeight& weight = inputBone->mWeights[weightIndex];
						auto& vertex = info.mMesh.mVertices[weight.mVertexId];
						auto& count = numWeigths[weight.mVertexId];

						if (count < 4)			//engine supports atmost 4 weights for 4 bones
						{
							vertex.boneIndecies[count] = boneIndex;
							vertex.boneWeights[count] = weight.mWeight;
							++count;
						}
					}
				}
			}
			model.mMeshes.emplace_back(info);

			model.meshFormat = forma;

			printf("\nloaded mesh %i.\n", index + 1);
		}
	}

	 //look for materials
	if (scene->HasMaterials())
	{
		printf("Reading Materials...\n");

		model.mMaterials.reserve(scene->mNumMaterials);

		for (uint32_t i = 0; i < scene->mNumMaterials; ++i)
		{
			Vishv::Graphics::ModelImport::MaterialData data;

			const aiMaterial* inputMaterial = scene->mMaterials[i];
			const uint32_t textureCountDiffuse = inputMaterial->GetTextureCount(aiTextureType_DIFFUSE);
			const uint32_t textureCountNormal = inputMaterial->GetTextureCount(aiTextureType_NORMALS);
			const uint32_t textureCountHeight = inputMaterial->GetTextureCount(aiTextureType_HEIGHT);
			const uint32_t textureCountSpecular = inputMaterial->GetTextureCount(aiTextureType_SPECULAR);
			if (textureCountDiffuse > 0)
			{
				aiString texturePath;
				if (inputMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
				{
					GetTexture(data.diffuseName, scene, "_diffuse_",i, texturePath, args);
				}
			}
			if (textureCountNormal > 0)
			{
				aiString texturePath;
				if (inputMaterial->GetTexture(aiTextureType_NORMALS, 0, &texturePath) == AI_SUCCESS)
				{
					GetTexture(data.normalName, scene, "_normal_", i,texturePath, args);
				}
			}
			//if (textureCountHeight > 0)
			//{
			//	aiString texturePath;
			//	if (inputMaterial->GetTexture(aiTextureType_HEIGHT, i, &texturePath) == AI_SUCCESS)
			//	{
			//		GetTexture(data.bumpName, scene, "_bump_", texturePath, args);
			//	}
			//}
			if (textureCountSpecular > 0)
			{
				aiString texturePath;
				if (inputMaterial->GetTexture(aiTextureType_SPECULAR, 0, &texturePath) == AI_SUCCESS)
				{
					GetTexture(data.specularName, scene, "_specular_",i, texturePath, args);
				}
			}

			model.mMaterials.emplace_back(data);
		}
	}

	//Check for skeleton information
	if (!skeleton.bones.empty())
	{
		printf("Building Skeleton....\n");
		skeleton.root = BuildSkeleton(*scene->mRootNode, nullptr, skeleton, boneIndexLookUp);
	}

	//Check for animation information
	if (scene->HasAnimations())
	{
		printf("Reading Animations...\n");

		for (uint32_t animIndex = 0; animIndex < scene->mNumAnimations; ++animIndex)
		{
			const aiAnimation* inputAnim = scene->mAnimations[animIndex];
			auto& animClip = animationsClips.emplace_back(std::make_unique<AnimationClip>());

			if (inputAnim->mName.length > 0)
				animClip->name = inputAnim->mName.C_Str();
			else
				animClip->name = "Anim_" + std::to_string(animIndex);

			animClip->duration = static_cast<float>(inputAnim->mDuration);
			animClip->ticksPerSecond = static_cast<float>(inputAnim->mTicksPerSecond);

			printf("Reading bone animations for %s... \n", animClip->name.c_str());

			//Reserve space so we have one animationspot per bopne, note that
			//not all bones will have animations so some slots will remain empty. however
			//keeping them the same size means we can use bone index directly to lookup animations
			animClip->boneAnimations.resize(skeleton.bones.size());
			for (uint32_t boneAnimationIndex = 0; boneAnimationIndex < inputAnim->mNumChannels; ++boneAnimationIndex)
			{
				const aiNodeAnim* inputBoneAnim = inputAnim->mChannels[boneAnimationIndex];
				int slotIndex = boneIndexLookUp[inputBoneAnim->mNodeName.C_Str()];
				auto& boneAnim = animClip->boneAnimations[slotIndex];
				boneAnim = std::make_unique<BoneAnimation>();

				if (inputBoneAnim->mNodeName.C_Str() > 0)
					boneAnim->name = inputBoneAnim->mNodeName.C_Str();
				else
					boneAnim->name = "Anim_" + std::to_string(boneAnimationIndex);

				AnimationBuilder builder;
				
				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumPositionKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mPositionKeys[keyIndex];
					builder.AddPositionKey({ Convert(key.mValue), static_cast<float>(key.mTime) });
				}
				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumRotationKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mRotationKeys[keyIndex];
					builder.AddRotationKey({ Convert(key.mValue), static_cast<float>(key.mTime) });
				}
				for (uint32_t keyIndex = 0; keyIndex < inputBoneAnim->mNumScalingKeys; ++keyIndex)
				{
					auto& key = inputBoneAnim->mScalingKeys[keyIndex];
					builder.AddScaleKey({ Convert(key.mValue), static_cast<float>(key.mTime) });
				}

				boneAnim->animation = builder.Build();

			}
		}
	}

	Vishv::Graphics::MeshIO mio;
	std::string fname = argsOpt.value().OutputFileName;
	std::filesystem::path pathF = fname;
	if (mio.SaveMesh(model, pathF))
	{
		printf("Saved Mesh\n");
	}

	Vishv::Graphics::SkeletonIO sIO;
	pathF.replace_extension() += ".vskel";
	if (sIO.SaveSkeleton(skeleton, pathF))
	{
		printf("\nSaved Skeleton\n");
	}

	Vishv::Graphics::AnimationIO aIO;
	pathF.replace_extension() += ".vanim";
	pathF = pathF.string().substr(0, pathF.string().rfind('\\') + 1);
	aIO.rootPath = pathF;
	fname.erase(0, fname.rfind("\\") + 1);
	pathF = fname;
	pathF.replace_extension();
	if (aIO.SaveAnimations(animationsClips, pathF.string()))
	{
		printf("\nSaved Animations\n");
	}



	//printf("couldnt write\n");

	return 0;
}