#ifndef INCLUDED_VISHV_GRAPHICS_LIGHT_H
#define INCLUDED_VISHV_GRAPHICS_LIGHT_H

#include "Colors.h"

namespace Vishv::Graphics {

struct PointLight
{
	Vishv::Math::Vector3 position;
	float padding;
	Color ambient;
	Color diffuse;
	Color specular;

};

struct DirectionalLight
{
	Vishv::Math::Vector3 direction;
	float padding;
	Color ambient;
	Color diffuse;
	Color specular;
};

}

#endif // !defined INCLUDED_VISHV_GRAPHICS_METERIAL_H