#ifndef INCLUDED_VISHV_GRAPHICS_METERIAL_H
#define INCLUDED_VISHV_GRAPHICS_METERIAL_H

#include "Colors.h"

namespace Vishv::Graphics {

struct Material
{
	Color ambient;
	Color diffuse;
	Color specular;
	float power;

	float padding[3];		//GPU needs to have 128 bits or 4 float or 16 bytes thus we add padding of 3 floats
};

}

#endif // !defined INCLUDED_VISHV_GRAPHICS_METERIAL_H