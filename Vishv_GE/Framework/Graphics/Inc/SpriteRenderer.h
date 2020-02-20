#ifndef INCLUDED_VISHV_GRAPHICS_SPRITERENDERER_H
#define INCLUDED_VISHV_GRAPHICS_SPRITERENDERER_H

namespace DirectX { class SpriteBatch; }

namespace Vishv::Graphics {

	class Texture;

class SpriteRenderer
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static SpriteRenderer* Get();

public:
	SpriteRenderer() = default;
	~SpriteRenderer();
	
	void Initialize();
	void Terminate();

	void BeginRender();
	void EndRender();

	void Draw(const Texture& texture, const Vishv::Math::Vector2& pos);

private:
	std::unique_ptr< DirectX::SpriteBatch> mSpriteBatch = nullptr;
};
}

#endif // defined INCLUDED_VISHV_GRAPHICS_SPRITERENDERER_H