#pragma once
#include "Vishv/Inc/Vishv.h"


namespace Vishv::UI
{
	class DrawShapeTool
	{
	public:
		void Initialize();

		void DrawUI();

		void SimpleDraw();

		bool GetObstacle(Vishv::Math::Shapes::Capsule& cap);
		bool GetWall(Vishv::Math::Shapes::Cuboid& wall);
	
	private:
		Vishv::Math::Shapes::Capsule capsuleSet;
		Vishv::Math::Shapes::Cuboid cuboidSet;

		bool isCapsule = false;
		bool isCuboid = false;

		Vishv::Math::Transform transformCap;
		Vishv::Math::Transform transformCuboid;

		Vishv::Graphics::Color capsuleColor = Vishv::Graphics::Colors::BlueViolet;
		Vishv::Graphics::Color cuboidColor = Vishv::Graphics::Colors::Coral;

		float capsuleHeight = 1.0f;
		float capsuleRadius = 1.0f;

		Math::Vector3 cuboidScale;
	};
}
