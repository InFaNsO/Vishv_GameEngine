#include "Precompiled.h"
#include "Skeleton.h"

using namespace Vishv::Graphics;
using namespace Vishv::Math;

void Vishv::Graphics::Skeleton::AddBone()
{
	Bone b;
	if (bones.size() == 0)
	{
		b.toParentTransform = Matrix4::Identity();
		b.index = 0;
		b.name = "root";
		b.parentId = -1;
		bones.push_back(std::make_unique<Bone>(std::move(b)));
		root = bones[0].get();
	}
	else
	{
		b.toParentTransform = bones[bones.size() - 1]->offsetTransform;
		b.index = static_cast<int>( bones.size());
	}

}

Bone* Vishv::Graphics::Skeleton::CreateBone(int parentIndex)
{
	VISHVASSERT((size_t) parentIndex < bones.size(), "[Graphics::Skeleton::GetTransformation] Parent Bone ID out of scope");
	Bone b;
	b.index = static_cast<int>(bones.size());
	b.parentId = parentIndex;// mSkeleton[parentIndex].id;
	b.parent = bones[parentIndex].get();
	int i = b.index;

	bones.push_back(std::make_unique<Bone>(std::move(b)));
	
	if (parentIndex >= 0 && parentIndex < (int)bones.size())
	{
		bones[parentIndex]->childIndicies.push_back(i);
		bones[parentIndex]->children.push_back(bones[i].get());
	}
	return bones[i].get();

	//for (size_t i = 0; i < mSkeleton.size(); ++i)
	//{
	//	if (mSkeleton[i].id == parentID)
	//	{
	//		Bone b;
	//		b.toParentTransform = mSkeleton[mSkeleton.size()].offsetTransform;
	//		b.id = mSkeleton.size();
	//
	//		mSkeleton.push_back(std::move(b));
	//	}
	//}
	//
	//return nullptr;

	//Bone* newBone = nullptr;
	//if (parentID < 0)
	//{
	//	//make root
	//	mRoot = std::make_unique<Bone>();
	//	newBone = mRoot.get();
	//}
	//
	//int id = mRoot->id;
	//auto current = mRoot.get();
	//
	//openList.clear();
	//closedList.clear();
	//
	//openList.push_back(mRoot.get());
	//bool found = false;
	//
	//while (parentID != id && !openList.empty())
	//{
	//	current = openList.front();
	//	openList.pop_front();
	//
	//	id = current->id;
	//
	//	if (id != parentID)
	//	{
	//		for (size_t i = 0; i < current->children.size(); ++i)
	//		{
	//			openList.push_back(current->children[i].get());
	//		}
	//	}
	//	else
	//		found = true;
	//	closedList.push_back(current);
	//}
	//
	//if (!found)
	//{
	//	//Paretn ID DoesNotExst
	//}
	//else
	//{
	//	current->children.push_back(std::move(bone));
	//}
}

Bone* Vishv::Graphics::Skeleton::GetBone()
{
	return bones.back().get();
}

Bone* Vishv::Graphics::Skeleton::GetBone(std::string name)
{
	if (bones.size() == 0)
	{
		return nullptr;
	}


	for (size_t i = 0; i < bones.size(); ++i)
	{
		if (bones[i]->name == name)
		{
			return bones[i].get();
		}
	}
	return nullptr;

	//Traversing the skeleton way
	//
	//
	//std::string na = mRoot->name;
	//auto current = mRoot.get();
	//
	//openList.clear();
	//closedList.clear();
	//
	//openList.push_back(mRoot.get());
	//bool found = false;
	//
	//while (na != name && !openList.empty())
	//{
	//	current = openList.front();
	//	openList.pop_front();
	//
	//	na = current->name;
	//
	//	if (na != name)
	//	{
	//		for (size_t i = 0; i < current->children.size(); ++i)
	//		{
	//			openList.push_back(current->children[i].get());
	//		}
	//	}
	//	else
	//		found = true;
	//	closedList.push_back(current);
	//}
	//
	//if (!found)
	//{
	//	//Name DoesNotExst
	//	return nullptr;
	//}
	//return Bone(current);
}


Matrix4 Vishv::Graphics::Skeleton::GetTransformation(size_t boneId)
{
	VISHVASSERT(boneId < bones.size(), "[Graphics::Skeleton::GetTransformation] Bone ID out of scope");

	if (bones[boneId]->parent != nullptr)
	{
		return bones[boneId]->toParentTransform * GetTransformation(bones[boneId]->parentId);
	}
	else
	{
		return bones[boneId]->toParentTransform;
	}
}

Bone* Vishv::Graphics::Skeleton::GetBone(int id)
{
	if (id < 0)
	{
		return nullptr;
	}

	for (size_t i = 0; i < bones.size(); ++i)
	{
		if (bones[i]->index == id)
			return bones[i].get();
	}

	return nullptr;

	//Traversing the skeleton
	//
	//
	//int Id = mRoot->id;
	//auto current = mRoot.get();
	//
	//openList.clear();
	//closedList.clear();
	//
	//openList.push_back(mRoot.get());
	//bool found = false;
	//
	//while (id != Id && !openList.empty())
	//{
	//	current = openList.front();
	//	openList.pop_front();
	//
	//	Id = current->id;
	//
	//	if (Id != id)
	//	{
	//		for (size_t i = 0; i < current->children.size(); ++i)
	//		{
	//			openList.push_back(current->children[i].get());
	//		}
	//	}
	//	else
	//		found = true;
	//	closedList.push_back(current);
	//}
	//
	//if (!found)
	//{
	//	//ID DoesNotExst
	//	return nullptr;
	//}
	//return std::make_shared<Bone>(current);
}

void Vishv::Graphics::Skeleton::Update()
{
}

void Vishv::Graphics::Skeleton::SetOffsetMat(size_t boneID, Math::Matrix4 & offset)
{
	VISHVASSERT(boneID >= bones.size(), "[Skeleton] BoneID out of range.");

	bones[boneID]->offsetTransform = offset;
}
void Vishv::Graphics::Skeleton::SetOffsetMat(size_t boneID, Math::Transform & offset)
{
	VISHVASSERT(boneID >= bones.size(), "[Skeleton] BoneID out of range.");

	bones[boneID]->offsetTransform = Math::Matrix4::RotateMatrix(offset.Rotation()) * Math::Matrix4::TranslateMatrix(offset.Position());
}
