#ifndef INCLUDED_VISHV_GRAPHICS_TEXTURE_H
#define INCLUDED_VISHV_GRAPHICS_TEXTURE_H

namespace Vishv{
namespace Graphics {

class Texture
{
public:
	enum class Type
	{
		none = -1,
		Bump,
		Diffuse,
		Normal,
		Specular
	};

public:
	Texture() = default;
	~Texture();

	void Initialize(const std::filesystem::path& fileName);
	void Terminate();

	void BindPS(uint32_t slot = 0) const;
	void BindVS(uint32_t slot = 0) const;

	Type GetType() { return mType; }
	void SetType(Type t) { mType = t; }

private:
	friend ID3D11ShaderResourceView* GetShaderResourceView(const Texture& texture);

	ID3D11ShaderResourceView* mShaderResourceView = nullptr;

	Type mType = Type::none;

};	//Texture

}	//Grphics
}	//Vishv

#endif // defined INCLUDED_VISHV_GRAPHICS_TEXTURE_H