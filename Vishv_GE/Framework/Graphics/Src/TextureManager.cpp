#include "Precompiled.h"
#include "TextureManager.h"
#include "Texture.h"


using namespace Vishv::Graphics;

namespace
{
	std::unique_ptr<TextureManager> sTextureManager = nullptr;
}

void Vishv::Graphics::TextureManager::StaticInitialize(std::filesystem::path rootPath)
{
	VISHVASSERT(sTextureManager == nullptr, "[Vishv::Graphics::TextureManager::StaticInitialize] Already static Initialized");

	sTextureManager = std::make_unique<TextureManager>();
	sTextureManager->SetRootPath(std::move(rootPath));
}

void Vishv::Graphics::TextureManager::StaticTerminate()
{
	if (sTextureManager != nullptr)
	{
		sTextureManager= nullptr;
	}
}

TextureManager * Vishv::Graphics::TextureManager::Get()
{
	return sTextureManager.get();
}

void Vishv::Graphics::TextureManager::SetRootPath(std::filesystem::path rootPath)
{
	VISHVASSERT(std::filesystem::is_directory(rootPath), "[Vishv::Graphics::TextureManager] %ls is not a directory.", rootPath.c_str());
	mRootPath = std::move(rootPath);
}

TextureID Vishv::Graphics::TextureManager::LoadTexture(std::filesystem::path fileName, bool isUsingRootpath)
{
	auto hash = std::filesystem::hash_value(fileName);

	auto[iter, success] = mInventory.insert({ hash, nullptr });
	if (success)
	{
		iter->second = std::make_unique<Texture>();
		iter->second->Initialize(isUsingRootpath ? mRootPath / fileName : fileName);
	}
	return hash;
}

Texture* Vishv::Graphics::TextureManager::GetTexture(TextureID texureID)
{
	if (auto iter = mInventory.find(texureID);
		iter != mInventory.end())
	{
		return iter->second.get();
	}

	return nullptr;
}

Vishv::Graphics::TextureManager::~TextureManager()
{
	for (auto&[key, value] : mInventory)
	{
		value->Terminate();
	}

	//to do
	//-add error checking
	//-add unload specific texture
	//-maybe do texture group
}

