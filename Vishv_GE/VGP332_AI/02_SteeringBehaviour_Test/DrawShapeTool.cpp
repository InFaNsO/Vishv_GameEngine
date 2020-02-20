#include "DrawShapeTool.h"

void Vishv::UI::DrawShapeTool::Initialize()
{
}

void Vishv::UI::DrawShapeTool::DrawUI()
{
	ImGui::Begin("Draw Shapes");

	if (ImGui::CollapsingHeader("Capsule"))
	{
		if (ImGui::DragFloat3("Position##Capsule", &capsuleSet.mTransform.mPosition.x, 0.5f))
			isCapsule = false;

		Math::Vector3 rot;

		//Need to rotate from local center not global
		//if (ImGui::DragFloat3("Rotation##Capsule", &rot.x, 1.f))
		//{
		//	if (rot.x != 0.0f)
		//		capsuleSet.mTransform.RotateX(rot.x);
		//	if (rot.y != 0.0f)
		//		capsuleSet.mTransform.RotateY(rot.y);
		//	if (rot.z != 0.0f)
		//		capsuleSet.mTransform.RotateZ(rot.z);
		//}

		if (ImGui::DragFloat("Height##Capsule", &capsuleHeight, 0.1f))
		{
			capsuleSet.SetHeight(capsuleHeight);
			isCapsule = false;
		}
		if (ImGui::DragFloat("Radius##Capsule", &capsuleSet.mRadius, 0.1f))
			isCapsule = false;
		ImGui::ColorEdit4("Color##Capsule", &capsuleColor.x);


		if (ImGui::Button("Set##capsule"))
		{
			isCapsule = true;
		}
	}
	if (ImGui::CollapsingHeader("Cuboid"))
	{
		if (ImGui::DragFloat3("Position##Cuboid", &cuboidSet.mTransform.mPosition.x, 0.5f))
			isCuboid = false;

		Math::Vector3 rot;

		//Need to rotate from local center not global
		if (ImGui::DragFloat3("Rotation##Cuboid", &rot.x, 1.f))
		{
			if (rot.x != 0.0f)
				cuboidSet.mTransform.RotateX(rot.x);
			if (rot.y != 0.0f)
				cuboidSet.mTransform.RotateY(rot.y);
			if (rot.z != 0.0f)
				cuboidSet.mTransform.RotateZ(rot.z);
		}

		if (ImGui::DragFloat3("scale##Cuboid", &cuboidScale.x, 0.1f))
		{
			cuboidSet.SetLengthX(cuboidScale.x);
			cuboidSet.SetLengthY(cuboidScale.y);
			cuboidSet.SetLengthZ(cuboidScale.z);
			isCuboid = false;
		}
		ImGui::ColorEdit4("Color##Cuboid", &cuboidColor.x);


		if (ImGui::Button("Set##cuboid"))
		{
			isCuboid = true;
		}
	}

	ImGui::End();
}

void Vishv::UI::DrawShapeTool::SimpleDraw()
{
	Vishv::Graphics::SimpleDraw::AddCapsule(capsuleSet, capsuleColor);
	Vishv::Graphics::SimpleDraw::AddCuboid(cuboidSet, cuboidColor);
}

bool Vishv::UI::DrawShapeTool::GetObstacle(Vishv::Math::Shapes::Capsule & cap)
{
	if (isCapsule)
	{
		cap = capsuleSet;
		isCapsule = false;
		return true;
	}
	return false;
}

bool Vishv::UI::DrawShapeTool::GetWall(Vishv::Math::Shapes::Cuboid & wall)
{
	if (isCuboid)
	{
		wall = cuboidSet;
		isCuboid = false;
		return true;
	}
	return false;
}

