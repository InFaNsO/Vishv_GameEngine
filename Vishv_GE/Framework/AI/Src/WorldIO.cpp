#include "Precompiled.h"
#include "WorldIO.h"
#include "World.h"

namespace
{
	std::string ToString(const Vishv::Math::Shapes::Capsule& cap)
	{
		std::string txt;
		txt += "Position: " + cap.mTransform.Position().ToString() + "\n";
		txt += "Rotation: " + cap.mTransform.Rotation().ToString() + "\n";
		txt += "Radius: " + std::to_string(cap.mRadius) + "\n";
		txt += "Height: " + std::to_string(cap.GetHeight()) + "\n";

		return std::move(txt);
	}

	std::string ToString(const Vishv::Math::Shapes::Cuboid& c)
	{
		std::string txt;
		txt += "Position: " + c.mTransform.Position().ToString() + "\n";
		txt += "Rotation: " + c.mTransform.Rotation().ToString() + "\n";
		txt += "LengthX: " + std::to_string(c.GetLengthX()) + "\n";
		txt += "LengthY: " + std::to_string(c.GetLengthY()) + "\n";
		txt += "LengthZ: " + std::to_string(c.GetLengthZ()) + "\n";

		return std::move(txt);
	}
}

void Vishv::AI::WorldIO::Save(std::filesystem::path path, const World & world)
{
	std::fstream file;
	file.open(path, std::ios::out);
	file.close();
	file.open(path);
	if (!file.is_open())
		return;

	file << "NumberObstacles: " << world.GetObstacles().size() << std::endl;
	file << "NumberWalls: " << world.GetWalls().size() << std::endl;

	for (size_t i = 0; i < world.GetObstacles().size(); ++i)
		file << ToString(world.GetObstacles()[i]);
	for (size_t i = 0; i < world.GetWalls().size(); ++i)
		file << ToString(world.GetWalls()[i]);
}

void Vishv::AI::WorldIO::Load(std::filesystem::path path, World & world)
{
	std::fstream file;
	file.close();
	file.open(path);
	if (!file.is_open())
		return;

	size_t maxObs, maxWall;
	std::string holder;

	file >> holder >> maxObs >> holder >> maxWall;

	world.GetObstacles().reserve(maxObs);
	world.GetWalls().reserve(maxWall);

	for (size_t i = 0; i < maxObs; ++i)
	{
		World::Obstacle obs;
		Math::Vector3 pr;
		Math::Quaternion q;
		file >> holder >> pr.x >> pr.y >> pr.z;
		obs.mTransform.mPosition = pr;
		file >> holder >> q.w >> q.x >> q.y >> q.z;
		obs.mTransform.SetRotation(std::move(q));
		float h;
		file >> holder >> obs.mRadius >> holder >> h;
		obs.SetHeight(h);

		world.Register(obs);
	}
	for (size_t i = 0; i < maxWall; ++i)
	{
		World::Wall wall;
		Math::Vector3 pr;
		Math::Quaternion q;
		file >> holder >> pr.x >> pr.y >> pr.z;
		wall.mTransform.mPosition = pr;
		file >> holder >> q.w >> q.x >> q.y >> q.z;
		wall.mTransform.SetRotation(std::move(q));
		file >> holder >> pr.x >> holder >> pr.y >> holder >> pr.z;

		wall.SetLengthX(pr.x);
		wall.SetLengthY(pr.y);
		wall.SetLengthZ(pr.z);

		world.Register(wall);
	}
}

