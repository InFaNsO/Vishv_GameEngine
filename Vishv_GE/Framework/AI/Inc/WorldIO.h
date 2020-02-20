#ifndef INCLUDED_VISHV_AI_WORLD_IO_H
#define INCLUDED_VISHV_AI_WORLD_IO_H

namespace Vishv::AI
{
	class World;
	class WorldIO
	{
	public:
		static void Save(std::filesystem::path path, const World& world);

		static void Load(std::filesystem::path path, World& world);

	private:
	};
}

#endif // !INCLUDED_VISHV_AI_WORLD_IO_H


