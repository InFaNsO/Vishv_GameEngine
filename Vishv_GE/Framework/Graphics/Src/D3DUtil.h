#ifndef INCLUDED_VISHV_GRAPHICS_DUTIL_H
#define INCLUDED_VISHV_GRAPHICS_DUTIL_H


namespace Vishv::Graphics{

class Texture;


	ID3D11ShaderResourceView* GetShaderResourceView(const Texture& texture);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
}

#endif // !INCLUDED_VISHV_GRAPHICS_DUTIL_H

