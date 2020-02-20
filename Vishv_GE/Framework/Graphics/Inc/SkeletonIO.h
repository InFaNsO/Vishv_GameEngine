#ifndef INCLUDED_VISHV_GRAPHICS_SKELETON_IO_H
#define INCLUDED_VISHV_GRAPHICS_SKELETON_IO_H

namespace Vishv::Graphics
{
	class Skeleton;

	class SkeletonIO
	{
	public:
		bool SaveSkeleton(Skeleton& skeleton, std::string name);

		bool SaveSkeleton(Skeleton& skeleton, std::filesystem::path path);

		bool LoadSkeleton(std::string name, Skeleton& skeleton);
		bool LoadSkeleton(std::filesystem::path filePath, Skeleton& skeleton);

		std::filesystem::path rootPath = L"../../Assets/3D_Models/";

	private:
		void Connect(Skeleton& skeleton);
	};
}

#endif // !INCLUDED_VISHV_GRAPHICS_SKELETON_IO_H




