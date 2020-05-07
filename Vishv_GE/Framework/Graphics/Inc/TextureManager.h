#ifndef INCLUDED_VISHV_GRAPHICS_TEXTURE_MANAGER_H
#define INCLUDED_VISHV_GRAPHICS_TEXTURE_MANAGER_H

namespace Vishv::Graphics {

using TextureID = size_t;

class Texture;

class TextureManager
{
public:
	static void StaticInitialize(std::filesystem::path rootPath);
	static void StaticTerminate();
	static TextureManager* Get();

public:
	TextureManager() = default;
	~TextureManager();

	void SetRootPath(std::filesystem::path rootPath);

	TextureID LoadTexture(std::filesystem::path fileName, bool usingRootPath = true);
	Texture* GetTexture(TextureID texureID);

	const std::filesystem::path& GetRootPath() { return mRootPath; }

private:
	std::filesystem::path mRootPath;
	std::unordered_map<TextureID, std::unique_ptr<Texture>> mInventory;

};
}
#endif // defined INCLUDED_VISHV_GRAPHICS_TEXTURE_MANAGER_H