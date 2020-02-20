#ifndef INCLUDED_VISHV_MATH_VISHV_RANDOM_H
#define INCLUDED_VISHV_MATH_VISHV_RANDOM_H

namespace Vishv::Math::Random
{
	inline float Float(float min = 0.0f, float max = 1.0f)
	{
		VISHVASSERT(min < max, "[Vishv::Math::Random] min value is greater than max");

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(min, max);

		return dist(mt);
	}

	inline float ZeroToOne()
	{
		static std::random_device rd;
		static std::mt19937 mt(rd());
		static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

		return dist(mt);
	}
}

#endif // Defined INCLUDED_VISHV_MATH_VISHV_RANDOM_H
