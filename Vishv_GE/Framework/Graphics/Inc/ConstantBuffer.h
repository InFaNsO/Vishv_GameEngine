#ifndef INCLUDED_VISHV_GRAPHICS_CONSTANT_BUFFER_H
#define INCLUDED_VISHV_GRAPHICS_CONSTANT_BUFFER_H

#include "Common.h"

namespace Vishv {
namespace Graphics {

class ConstantBuffer
{
public:
	void Initialize(uint32_t size = sizeof(Math::Matrix4));
	void Bind(const Math::Matrix4 matrix[]);
	void Set(const void* data) const;
	void BindVS(uint32_t slot = 0) const;
	void BindPS(uint32_t slot = 0) const;
	void BindGS(uint32_t slot = 0) const;
	void BindCS(uint32_t slot = 0) const;
	void Terminate();

	~ConstantBuffer();

private:
	ID3D11Buffer *constantBuffer{ nullptr };

};


template <class DataType>
class TypedConstantBuffer : public ConstantBuffer
{
public:
	void Initialize()
	{
		static_assert(sizeof(DataType) % 16 == 0, "[Vishv::Graphics::TypedConstantBuffer] Data type must be 16 bytes alligned.");
		ConstantBuffer::Initialize(sizeof(DataType));
	}
	void Initialize(const DataType& data)
	{
		ConstantBuffer::Initialize(sizeof(DataType));	//change this
	}
	void Set(const DataType& data) const
	{
		ConstantBuffer::Set(&data);
	}
};

}	//Graphics
}	//Vishv

#endif // !INCLUDED_VISHV_GRAPHICS_CONSTANT_BUFFER_H

