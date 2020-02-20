#pragma once
#include <random>

#include <Math/Inc/VishvMath.h>

struct ConvexShape
{
	std::vector<Vishv::Math::Vector3> mVertices;
	Vishv::Math::Vector4 mColor;
	Vishv::Math::Vector3 mCenter;
	int mSides;

	const float len = 30.0f;

	void Initialize(const Vishv::Math::Vector3 &center)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distAngle(10, 120);
		std::uniform_real_distribution<float> distColor(0.0f, 1.0f);

		mCenter = center;
		mVertices.clear();

		
		for (float angle = 0.0f; angle <= Vishv::Math::Constans::TwoPi; )
		{
			Vishv::Math::Vector3 side(len * cos(angle) + mCenter.x, len *sin(angle) + mCenter.y, 0.0f + mCenter.z);
			mVertices.push_back(side);

			float angleInc = distAngle(mt);
			angleInc *= Vishv::Math::Constans::DegToRad;
			angle += angleInc;
		}

		mSides = (int)mVertices.size();
		mColor = { distColor(mt), distColor(mt), distColor(mt), 1.0f };
	}

	void Update(Vishv::Math::Vector3 pos)
	{
		for (auto &it : mVertices)
		{
			it += pos - mCenter;
		}

		mCenter = pos;
	}

	void Draw(bool isSolid = true, bool is2d = false)
	{
		if (!is2d)
		{

		}

		if (is2d)
		{
			for (int i = 0; i < mVertices.size() - 1; ++i)
			{
				//X::DrawScreenLine({ mVertices[i].x, mVertices[i].y }, { mVertices[i + 1].x, mVertices[i + 1].y }, mColor);
			}

			//X::DrawScreenLine({ mVertices[mSides - 1].x, mVertices[mSides - 1].y }, { mVertices[0].x, mVertices[0].y }, mColor);

			if (isSolid)
			{
				for (int i = 0; i < mSides; ++i)
				{
					for (int j = 0; j < mSides; ++j)
					{
						if (j != i)
						{
							//X::DrawScreenLine(mVertices[i].x, mVertices[i].y, mVertices[j].x, mVertices[j].y, mColor);

						}
					}
				}
			}
		}
	}

	ConvexShape operator= (const ConvexShape& other)
	{
		mVertices = other.mVertices;
		mColor = other.mColor;
		mCenter = other.mCenter;
		mSides = other.mSides;
		return *this;
	}
};