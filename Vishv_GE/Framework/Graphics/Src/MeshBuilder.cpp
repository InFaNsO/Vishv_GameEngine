#include "Precompiled.h"
#include "MeshBuilder.h"
#include <random>

using namespace Vishv;
using namespace Vishv::Graphics;

#pragma region Bone Meshes
BoneMesh Vishv::Graphics::Meshbuilder::CreateBoneCube(float height, float width, float depth, int boneIndex)
{
	float halfHeight = height * 0.5f;
	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	std::vector<BoneVertex> vertices;
	vertices.resize(16);

	//Front Face
	vertices[0] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.75f, 1.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f}};		//Front top left		00
	vertices[1] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.00f, 1.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f}};		//Front top Right		01
	vertices[2] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.75f, 2.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f}};		//Front Buttom Left		02
	vertices[3] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.00f, 2.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f}};		//Front Buttom Right	03

	//Buttom Face
	vertices[4] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.25f, 1.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front Buttom Left		04
	vertices[5] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.50f, 1.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front Buttom Right	05
	vertices[6] = { { -1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.25f, 2.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Back Buttom Left		06
	vertices[7] = { {  1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.50f, 2.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Back Buttom Right		07

	//Top Face
	vertices[8] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.25f, 0.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front top left		08
	vertices[9] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.05f, 0.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front top Right		09
	vertices[10] = { { -1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.25f, 1.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Back top left			10
	vertices[11] = { {  1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.50f, 1.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Back top Right		11

	//Left Face only 2 at the left (front vertices)
	vertices[12] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f , 1.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front top left		12
	vertices[13] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f , 2.0f / 3.0f}, {boneIndex, boneIndex, boneIndex, boneIndex}, {1.0f, 0.0f, 0.0f, 0.0f} };		//Front Buttom Left		13

	constexpr uint32_t indices[] =
	{
		0,1,2,		//|
		1,3,2,		//|--- Front face

		11,7,3,		//|
		3,9,11,		//|--- Right face

		6,11,10,	//|
		6,7,11,		//|--- Back face

		10,12,13,	//|
		13,6,10,	//|--- Left face

		8,10,11,	//|
		11,9,8,		//|--- Top face

		4,5,7,		//|
		7,6,4		//|--- Bottom face
	};

	BoneMesh mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices.insert(mesh.mIndices.end(), std::begin(indices), std::end(indices));

	return mesh;
}

BoneMesh Vishv::Graphics::Meshbuilder::CreateBoneCylinder(int rows, int col, float radius, float thicknessRow, int totalBones, int boneAffect, bool capped)
{
	boneAffect = 3; //this is temporary to test can be romoved or kept for ever

	VISHVASSERT(rows >= 3 && rows % 2 == 1, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder or not odd to have proper bones");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");
	VISHVASSERT(totalBones > 0., "[MeshBuilder::BoneCylender] Number of bones has to be more than 0");
	VISHVASSERT(boneAffect > 0 && boneAffect <= 3, "[MeshBuilder::BoneCylender] boneAffect has to be atleast 1 and at most 3");

	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 2;
	}

	//create vertices
	std::vector<BoneVertex> vertices;
	vertices.resize(numVertices);

	float bpr  = static_cast<float>( totalBones  - 2)/ static_cast<float>(rows - 1);
	//float perWeight = 

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, -(rows * thicknessRow) / 2, 0.0f);
	start.y = 0.0f - ((float)rows * 0.5f);

	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * radius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * radius;	//cos theta
			vertices[index].position.y = (i * thicknessRow) + start.y;				//Affected by row

			vertices[index].normal = start - vertices[index].position;//set this

						//Setting UV
			vertices[index].texCoord.x = static_cast<float>(j) / (col);
			vertices[index].texCoord.y = static_cast<float>(i) / (rows);

			//setting bones and weights
			for (int k = 0; k < boneAffect; ++k)
			{
				if (i == 0)																//if bace
					vertices[index].boneIndecies[k] = 0;
				else if (i == rows)														//if top
					vertices[index].boneIndecies[k] = totalBones - 1;
				else																	//others
				{
					float m = fmodf( (i * bpr) ,1.0f);
					int bid = m > 0.0f ? static_cast<int>(i * bpr) + 1 : static_cast<int>(i * bpr);

					vertices[index].boneIndecies[k] = bid;

					if (k == 0 && bid > 1)
						vertices[index].boneIndecies[k] -= 1;
					else if (k == 1)
						vertices[index].boneIndecies[k] += 0;
					else if(k == 2 && bid < totalBones - 2)
						vertices[index].boneIndecies[k] += 1;
				}

				if (k == 0 && i == 0 || k == 0 && i == rows)
				{
					vertices[index].boneWeights[k] = 1.0f;
				}
				else if (i == 0 || i == rows)
				{
					vertices[index].boneWeights[k] = 0.0f;
				}
				else
				{
					if(k == 0)
						vertices[index].boneWeights[k] = 0.33f;
					else if (k == 1)
						vertices[index].boneWeights[k] = 0.34f;
					else if (k == 2)
						vertices[index].boneWeights[k] = 0.33f;
				}
			}

			currentAngle -= deltaAngle;

		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 2].boneWeights[0] = 1.0f;

		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = (rows * thicknessRow)  * 0.5f;
		vertices[numVertices - 1].boneIndecies[0] = totalBones - 1;
		vertices[numVertices - 1].boneWeights[0] = 1.0f;

		vertices[numVertices - 2].normal = { 0.0f, -1.0f, 0.0f };
		vertices[numVertices - 1].normal = { 0.0f, 1.0f, 0.0f };
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		//vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += (col * 2) * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	////imagnary boxes
	//int imgBox = rows;
	//for (int boxnum = 0; boxnum < imgBox; boxnum++)
	//{
	//	int currentImgBoxNum = boxnum + (col * (boxnum + 1));
	//
	//	indices[currentIndex] = currentImgBoxNum;
	//	indices[currentIndex + 1] = currentImgBoxNum - col;
	//	indices[currentIndex + 2] = currentImgBoxNum + col + 1;
	//
	//	indices[currentIndex + 3] = currentImgBoxNum - col;
	//	indices[currentIndex + 4] = currentImgBoxNum + 1;
	//	indices[currentIndex + 5] = currentImgBoxNum + col + 1;
	//
	//	currentIndex += 6;
	//}

	if (capped)
	{
		//make triangle fan
		//on top and buttom

		//buttom
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 2;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}

		//top
		for (int triNum = numVertices - col - ((capped) ? 3 : 1); triNum < numVertices - ((capped) ? 3 : 1); ++triNum)
		{
			indices[currentIndex] = triNum + ((triNum == col - 1) ? 0 : 1);
			indices[currentIndex + 2] = triNum;
			indices[currentIndex + 1] = numVertices - 1;

			currentIndex += 3;
		}
	}


	BoneMesh mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}
#pragma endregion 

#pragma region Color Meshes

MeshPC Vishv::Graphics::Meshbuilder::CreateCubePC(float height, float width, float depth)
{
	float halfHeight = height * 0.5f;
	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	std::vector<VertexPC> vertices;
	vertices.resize(14);

	//Front Face
	vertices[0]		= { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front top left		00
	vertices[1]		= { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front top Right		01
	vertices[2]		= { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front Buttom Left		02
	vertices[3]		= { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front Buttom Right	03

	//Buttom Face
	vertices[4]		= { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front Buttom Left		04
	vertices[5]		= { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front Buttom Right	05
	vertices[6]		= { { -1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Back Buttom Left		06
	vertices[7]		= { {  1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Back Buttom Right		07

	//Top Face
	vertices[8]		= { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front top left		08
	vertices[9]		= { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front top Right		09
	vertices[10]	= { { -1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Back top left			10
	vertices[11]	= { {  1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Back top Right		11

	//Left Face only 2 at the left (front vertices)
	vertices[12]	= { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front top left		12
	vertices[13]	= { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { dist(mt), dist(mt), dist(mt), 1.0f } };		//Front Buttom Left		13


	constexpr uint32_t indices[] =
	{
		0,1,2,		//|
		1,3,2,		//|--- Front face

		11,7,3,		//|
		3,9,11,		//|--- Right face

		6,11,10,	//|
		6,7,11,		//|--- Back face

		10,12,13,	//|
		13,6,10,	//|--- Left face

		8,10,11,	//|
		11,9,8,		//|--- Top face

		4,5,7,		//|
		7,6,4		//|--- Bottom face
	};
	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices.insert(mesh.mIndices.end(), std::begin(indices), std::end(indices));

	return mesh;
}

MeshPC Vishv::Graphics::Meshbuilder::CreatePlanePC(int rows, int col, float thicknessRow, float thicknessCol)
{
	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	int numVertices = (rows + 1) * (col + 1);

	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);

	for (int i = 0; i <= rows; ++i)
	{
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			int index = j + (i * (col + 1));
			vertices[index].position.z = 0.0f;	//no thickness
			vertices[index].position.x = j * thicknessCol;	//affected by col
			vertices[index].position.y = i * thicknessRow;	//Affected by row
		}

	}

	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex]		= boxNum + (boxNum / col);
		indices[currentIndex + 1]	= boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2]	= indices[currentIndex] + col + 1;

		indices[currentIndex + 3]	= boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4]	= indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5]	= indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPC Vishv::Graphics::Meshbuilder::CreateCylinderPC(int rows,  int col, float radius, float thicknessRow, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder.");
	VISHVASSERT(col  >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 2;
	}

	//create vertices
	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);


	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * radius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * radius;	//cos theta
			vertices[index].position.y = i * thicknessRow;				//Affected by row

			currentAngle -= deltaAngle;

		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = rows * thicknessRow;
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += (col * 2) * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	////imagnary boxes
	//int imgBox = rows;
	//for (int boxnum = 0; boxnum < imgBox; boxnum++)
	//{
	//	int currentImgBoxNum = boxnum + (col * (boxnum + 1));
	//
	//	indices[currentIndex] = currentImgBoxNum;
	//	indices[currentIndex + 1] = currentImgBoxNum - col;
	//	indices[currentIndex + 2] = currentImgBoxNum + col + 1;
	//
	//	indices[currentIndex + 3] = currentImgBoxNum - col;
	//	indices[currentIndex + 4] = currentImgBoxNum + 1;
	//	indices[currentIndex + 5] = currentImgBoxNum + col + 1;
	//
	//	currentIndex += 6;
	//}

	if (capped)
	{
		//make triangle fan
		//on top and buttom

		//buttom
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex]		= triNum;
			indices[currentIndex + 1]	= numVertices - 2;
			indices[currentIndex + 2]	= triNum + ((triNum == col ) ? 0 : 1);

			currentIndex += 3;
		}

		//top
		for (int triNum = numVertices - col - ((capped) ? 3 : 1); triNum < numVertices - ((capped) ? 3 : 1); ++triNum)
		{
			indices[currentIndex] = triNum + ((triNum == col - 1) ? 0 : 1);
			indices[currentIndex + 2] = triNum;
			indices[currentIndex + 1] = numVertices - 1;

			currentIndex += 3;
		}
	}


	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPC Vishv::Graphics::Meshbuilder::CreateConePC(int rows, int col, float radius, float thicknessRow, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCone] To few rows to generate a cone.");
	VISHVASSERT(col  >= 3, "[Vishv::Graphics::Meshbuilder::CreateCone] To few columns to generate a cone.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 1;
	}

	//create vertices
	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);
	const float maxHeight = rows * thicknessRow;
	const float percent = thicknessRow / maxHeight;

	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = radius;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * currentRadius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * currentRadius;	//cos theta
			vertices[index].position.y = i * thicknessRow;						//Affected by row

			currentAngle -= deltaAngle;

		}
		currentRadius -= radius * percent;
	}
	if (capped)
	{
		//set the center points for buttom
		vertices[numVertices - 1].position = start;		//buttom peice
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += col * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	if (capped)
	{
		//make triangle fan
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 1;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}
	}


	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPC Vishv::Graphics::Meshbuilder::CreateSpherePC(int rows, int col, float radius)
{
	VISHVASSERT(rows >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few rows to generate a sphere.");
	VISHVASSERT(col  >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few columns to generate a sphere.");

	Math::Vector3 center;
	center.y = radius;


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);



	//create vertices
	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(rows);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius	= 0.0f;
	float currentAngleY	= 0.0f;
	float thicknessRow	= 0.0f;

	bool half = false;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleX = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngleX) * currentRadius;	//sin theta
			vertices[index].position.x = (cosf(currentAngleX) * currentRadius) - radius;	//cos theta
			vertices[index].position.y = (thicknessRow) - radius;							//Affected by row

			currentAngleX -= deltaAngleX;

		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) half = true;



		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);
		
		thicknessRow = ((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f);
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPC Vishv::Graphics::Meshbuilder::CreateTorusPC(int rows, int col, float innerRadius, float outerRadius)
{
	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	const float radius = (outerRadius - innerRadius) / 2.0f;
	const float R = innerRadius + radius;
	int numVertices = (col + 1) * (rows + 1);

	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	const float deltaAngleIn  = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;
	const float deltaAngleOut = (360.0f / static_cast<float>(rows)) * Math::Constans::DegToRad;

	float currentAngleOut = 0.0f;

	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleIn = 0.0f;
		for (int j = 0; j <= col; ++j)
		{
			int index = j + (i * (col + 1));

			vertices[index].position.x = (R + radius * cosf(currentAngleIn)) * cosf(currentAngleOut);
			vertices[index].position.y = (R + radius * cosf(currentAngleIn)) * sinf(currentAngleOut);
			vertices[index].position.z = radius * sinf(currentAngleIn);

			currentAngleIn += deltaAngleIn;
		}

		currentAngleOut += deltaAngleOut;
	}

	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPC mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

#pragma endregion

#pragma region Normal Meshes

MeshPN Vishv::Graphics::Meshbuilder::CreateSphereNormal(int rows, int col, float radius)
{
	VISHVASSERT(rows >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few rows to generate a sphere.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few columns to generate a sphere.");

	Math::Vector3 center;
	center.y = radius;

	int numVertices = (rows + 1) * (col + 1);

	//create vertices
	std::vector<VertexPN> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, radius,0.0f);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(rows);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float thicknessRow = 0.0f;

	bool half = false;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleX = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngleX) * currentRadius;		//sin theta
			vertices[index].position.x = (cosf(currentAngleX) * currentRadius) ;	//cos theta
			vertices[index].position.y = start.y - thicknessRow;					//Affected by row

			vertices[index].normal = Vishv::Math::Normalize(vertices[index].position);

			currentAngleX -= deltaAngleX;

		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) half = true;



		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);

		thicknessRow = ((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f);
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPN mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPN Vishv::Graphics::Meshbuilder::CreateCylinderNormal(int rows, int col, float radius, float thicknessRow, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 2;
	}

	//create vertices
	std::vector<VertexPN> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, (rows * thicknessRow) / 2 ,0.0f);


	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * radius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * radius;	//cos theta
			vertices[index].position.y = start.y -  i * thicknessRow;				//Affected by row

			vertices[index].normal = start - vertices[index].position;//set this

			currentAngle -= deltaAngle;

		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = rows * thicknessRow;
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		//vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += (col * 2) * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	////imagnary boxes
	//int imgBox = rows;
	//for (int boxnum = 0; boxnum < imgBox; boxnum++)
	//{
	//	int currentImgBoxNum = boxnum + (col * (boxnum + 1));
	//
	//	indices[currentIndex] = currentImgBoxNum;
	//	indices[currentIndex + 1] = currentImgBoxNum - col;
	//	indices[currentIndex + 2] = currentImgBoxNum + col + 1;
	//
	//	indices[currentIndex + 3] = currentImgBoxNum - col;
	//	indices[currentIndex + 4] = currentImgBoxNum + 1;
	//	indices[currentIndex + 5] = currentImgBoxNum + col + 1;
	//
	//	currentIndex += 6;
	//}

	if (capped)
	{
		//make triangle fan
		//on top and buttom

		//buttom
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 2;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}

		//top
		for (int triNum = numVertices - col - ((capped) ? 3 : 1); triNum < numVertices - ((capped) ? 3 : 1); ++triNum)
		{
			indices[currentIndex] = triNum + ((triNum == col - 1) ? 0 : 1);
			indices[currentIndex + 2] = triNum;
			indices[currentIndex + 1] = numVertices - 1;

			currentIndex += 3;
		}
	}


	MeshPN mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

#pragma endregion

#pragma region Texture Meshes

MeshPX Vishv::Graphics::Meshbuilder::CreateCubeUV(float height, float width, float depth)
{
	float halfHeight = height * 0.5f;
	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	std::vector<VertexPX> vertices;
	vertices.resize(14);

	//Front Face
	vertices[0] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  0.75f, 1.0f / 3.0f};		//Front top left		00
	vertices[1] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  1.00f, 1.0f / 3.0f};		//Front top Right		01
	vertices[2] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  0.75f, 2.0f / 3.0f};		//Front Buttom Left		02
	vertices[3] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  1.00f, 2.0f / 3.0f};		//Front Buttom Right	03

	//Buttom Face
	vertices[4] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  0.25f, 1.0f		};		//Front Buttom Left		04
	vertices[5] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  0.50f, 1.0f		};		//Front Buttom Right	05
	vertices[6] = { { -1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth},  0.25f, 2.0f / 3.0f};		//Back Buttom Left		06
	vertices[7] = { {  1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth},  0.50f, 2.0f / 3.0f};		//Back Buttom Right		07

	//Top Face
	vertices[8] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  0.25f, 0.0f		};		//Front top left		08
	vertices[9] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  0.05f, 0.0f		};		//Front top Right		09
	vertices[10] = { { -1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, 0.25f, 1.0f / 3.0f};		//Back top left			10
	vertices[11] = { {  1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, 0.50f, 1.0f / 3.0f};		//Back top Right		11

	//Left Face only 2 at the left (front vertices)
	vertices[12] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, 0.0f , 1.0f / 3.0f };		//Front top left		12
	vertices[13] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, 0.0f , 2.0f / 3.0f };		//Front Buttom Left		13


	constexpr uint32_t indices[] =
	{
		0,1,2,		//|
		1,3,2,		//|--- Front face

		11,7,3,		//|
		3,9,11,		//|--- Right face

		6,11,10,	//|
		6,7,11,		//|--- Back face

		10,12,13,	//|
		13,6,10,	//|--- Left face

		8,10,11,	//|
		11,9,8,		//|--- Top face

		4,5,7,		//|
		7,6,4		//|--- Bottom face
	};
	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices.insert(mesh.mIndices.end(), std::begin(indices), std::end(indices));

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateSkyboxUV(float height, float width, float depth)

{
	float halfHeight = height * 0.5f;
	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	std::vector<VertexPX> vertices;
	vertices.resize(14);

	//Front Face
	vertices[0] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { 0.75f, 1.0f / 3.0f } };		//Front top left		00
	vertices[1] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, { 1.00f, 1.0f / 3.0f } };		//Front top Right		01
	vertices[2] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { 0.75f, 2.0f / 3.0f } };		//Front Buttom Left		02
	vertices[3] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, { 1.00f, 2.0f / 3.0f } };		//Front Buttom Right	03

	//Buttom Face
	vertices[4] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  {0.25f, 1.0f }};		//Front Buttom Left		04
	vertices[5] = { {  1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth},  {0.50f, 1.0f }};		//Front Buttom Right	05
	vertices[6] = { { -1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth},  {0.25f, 2.0f / 3.0f }};		//Back Buttom Left		06
	vertices[7] = { {  1.0f * halfWidth, -1.0f * halfHeight,  1.0f * halfDepth},  {0.50f, 2.0f / 3.0f }};		//Back Buttom Right		07

	//Top Face
	vertices[8] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  {0.25f, 0.0f} };		//Front top left		08
	vertices[9] = { {  1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth},  {0.05f, 0.0f} };		//Front top Right		09
	vertices[10] = { { -1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, {0.25f, 1.0f / 3.0f} };		//Back top left			10
	vertices[11] = { {  1.0f * halfWidth,  1.0f * halfHeight,  1.0f * halfDepth}, {0.50f, 1.0f / 3.0f} };		//Back top Right		11

	//Left Face only 2 at the left (front vertices)
	vertices[12] = { { -1.0f * halfWidth,  1.0f * halfHeight, -1.0f * halfDepth}, {0.0f , 1.0f / 3.0f }};		//Front top left		12
	vertices[13] = { { -1.0f * halfWidth, -1.0f * halfHeight, -1.0f * halfDepth}, {0.0f , 2.0f / 3.0f }};		//Front Buttom Left		13


	constexpr uint32_t indices[] =
	{
		2,1,0,		//|
		2,3,1,		//|--- Front face

		3,7,11,		//|
		11,9,3,		//|--- Right face

		10,11,6,	//|
		11,7,6,		//|--- Back face

		13,12,10,	//|
		10,6,13,	//|--- Left face

		11,10,8,	//|
		8,9,11,		//|--- Top face

		7,5,4,		//|
		4,6,7		//|--- Bottom face
	};
	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices.insert(mesh.mIndices.end(), std::begin(indices), std::end(indices));

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreatePlaneUV(int rows, int col, float thicknessRow, float thicknessCol)
{
	int numVertices = (rows + 1) * (col + 1);

	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);

	for (int i = 0; i <= rows; ++i)
	{
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			int index = j + (i * (col + 1));
			vertices[index].position.z = 0.0f;	//no thickness
			vertices[index].position.x = j * thicknessCol;	//affected by col
			vertices[index].position.y = i * thicknessRow;	//Affected by row

			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col );
			vertices[index].v = static_cast<float>(i) / (rows);
		}

	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateCylinderUV(int rows, int col, float radius, float thicknessRow, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 2;
	}

	//create vertices
	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);
	start.y = 0.0f - ((float)rows * 0.5f);


	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * radius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * radius;	//cos theta
			vertices[index].position.y = (i * thicknessRow) + start.y;				//Affected by row

			currentAngle -= deltaAngle;


			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col);
			vertices[index].v = static_cast<float>(i) / (rows);
		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 2].u = 0.5f;
		vertices[numVertices - 2].v = 0.5f;
	
		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = rows * thicknessRow;
		vertices[numVertices - 1].u = 0.5f;		//Top peice
		vertices[numVertices - 1].v = 0.5f;		//Top peice
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += (col * 2) * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	//make triangle fan
	if (capped)
	{
		//buttom
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 2;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}

		//top
		for (int triNum = numVertices - col - ((capped) ? 3 : 1); triNum < numVertices - ((capped) ? 3 : 1); ++triNum)
		{
			indices[currentIndex] = triNum + ((triNum == col - 1) ? 0 : 1);
			indices[currentIndex + 2] = triNum;
			indices[currentIndex + 1] = numVertices - 1;

			currentIndex += 3;
		}
	}


	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateConeUV(int rows, int col, float radius, float thicknessRow, bool capped)

{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCone] To few rows to generate a cone.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCone] To few columns to generate a cone.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 1;
	}

	//create vertices
	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);
	const float maxHeight = rows * thicknessRow;
	const float percent = thicknessRow / maxHeight;

	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = radius;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * currentRadius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * currentRadius;	//cos theta
			vertices[index].position.y = i * thicknessRow;						//Affected by row

			currentAngle -= deltaAngle;


			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col);
			vertices[index].v = static_cast<float>(i) / (rows);
		}
		currentRadius -= radius * percent;
	}
	if (capped)
	{
		//set the center points for buttom
		vertices[numVertices - 1].position = start;		//buttom peice
		vertices[numVertices - 1].u = 0.5f;		//buttom peice
		vertices[numVertices - 1].v = 0.5f;		//buttom peice
	}

	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += col * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	//make triangle fan
	if (capped)
	{
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 1;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}
	}


	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateSphereUV(int rows, int col, float radius)
{
	VISHVASSERT(rows >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few rows to generate a sphere.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few columns to generate a sphere.");

	int numVertices = (rows + 1) * (col + 1);

	//create vertices
	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, radius, 0.0f);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(rows);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float thicknessRow = 0.0f;

	bool half = false;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleX = 0.0f;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));
			vertices[index].position.z = sinf(currentAngleX) * currentRadius;		//sin theta
			vertices[index].position.x = (cosf(currentAngleX) * currentRadius);	//cos theta
			vertices[index].position.y = start.y - thicknessRow;					//Affected by row


			currentAngleX += deltaAngleX;


			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col);
			vertices[index].v = static_cast<float>(i) / (rows);
		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f)
			half = true;

		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);

		thicknessRow = ((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f);
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateSkyDomeUV(int rows, int col, float radius)

{
	VISHVASSERT(rows >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few rows to generate a sphere.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few columns to generate a sphere.");

	int numVertices = (rows + 1) * (col + 1);

	//create vertices
	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(rows);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float thicknessRow = 0.0f;

	bool half = false;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleX = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngleX) * currentRadius;	//sin theta
			vertices[index].position.x = cosf(currentAngleX) * currentRadius;	//cos theta
			vertices[index].position.y = thicknessRow;							//Affected by row

			currentAngleX -= deltaAngleX;


			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col);
			vertices[index].v = static_cast<float>(i) / (rows);
		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) half = true;



		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);

		thicknessRow = ((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f);
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex + 2] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 0] = indices[currentIndex + 2] + col + 1;

		indices[currentIndex + 5] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 3] = indices[currentIndex + 2] + col + 1;

		currentIndex += 6;
	}

	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateTorusUV(int rows, int col, float innerRadius, float outerRadius)
{
	const float radius = (outerRadius - innerRadius) / 2.0f;
	const float R = innerRadius + radius;
	int numVertices = (col + 1) * (rows + 1);

	std::vector<VertexPX> vertices;
	vertices.resize(numVertices);

	const float deltaAngleIn = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;
	const float deltaAngleOut = (360.0f / static_cast<float>(rows)) * Math::Constans::DegToRad;

	float currentAngleOut = 0.0f;

	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleIn = 0.0f;
		for (int j = 0; j <= col; ++j)
		{
			int index = j + (i * (col + 1));

			vertices[index].position.x = (R + radius * cosf(currentAngleIn)) * cosf(currentAngleOut);
			vertices[index].position.y = (R + radius * cosf(currentAngleIn)) * sinf(currentAngleOut);
			vertices[index].position.z = radius * sinf(currentAngleIn);

			currentAngleIn += deltaAngleIn;

			//Setting UV
			vertices[index].u = static_cast<float>(j) / (col);
			vertices[index].v = static_cast<float>(i) / (rows);
		}

		currentAngleOut += deltaAngleOut;
	}


	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	MeshPX mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

MeshPX Vishv::Graphics::Meshbuilder::CreateNDCQuad()
{
	MeshPX mesh;
	//
	// (-1, -1)---------------(+1, +1)
	//    |                      |
	//    |        (0,0)         |
	//    |                      |
	// (-1, -1)---------------(+1, -1)
	//
	mesh.mVertices.emplace_back(VertexPX{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
	mesh.mVertices.emplace_back(VertexPX{ { -1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } });
	mesh.mVertices.emplace_back(VertexPX{ { +1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } });
	mesh.mVertices.emplace_back(VertexPX{ { +1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });

	mesh.mIndices.emplace_back(0);
	mesh.mIndices.emplace_back(1);
	mesh.mIndices.emplace_back(2);
	
	mesh.mIndices.emplace_back(2);
	mesh.mIndices.emplace_back(3);
	mesh.mIndices.emplace_back(0);

	return mesh;
}

#pragma endregion

#pragma region NTX Mesh

Mesh Vishv::Graphics::Meshbuilder::CreateSphere(int rows, int col, float radius)
{
	VISHVASSERT(rows >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few rows to generate a sphere.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateSphere] To few columns to generate a sphere.");

	int numVertices = (rows + 1) * (col + 1);

	//create vertices
	std::vector<Vertex> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, radius, 0.0f);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(rows);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float thicknessRow = 0.0f;

	bool half = false;

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngleX = 0.0f;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));
			vertices[index].position.z = sinf(currentAngleX) * currentRadius;		//sin theta
			vertices[index].position.x = (cosf(currentAngleX) * currentRadius);	//cos theta
			vertices[index].position.y = start.y - thicknessRow;					//Affected by row


			currentAngleX += deltaAngleX;


			//Setting UV
			vertices[index].texCoord.x = static_cast<float>(j) / (col);
			vertices[index].texCoord.y = static_cast<float>(i) / (rows);

			//setting Normal
			vertices[index].normal = vertices[index].position;
			vertices[index].normal.Normalize();

			//setting Tangent
			vertices[index].tangent = Math::Vector3(-vertices[index].position.z, 0.0f, vertices[index].position.x);
			if(vertices[index].tangent.MagnitudeSq() != 0.0f)
				vertices[index].tangent.Normalize();

		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) 
			half = true;

		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);

		thicknessRow = ((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f);
	}

	int numIndices = ((rows * col) * 2) * 3;

	std::vector<uint32_t> indices;
	indices.resize(numIndices);

	int currentRow = 0, currentColumn = 0;

	int maxBox = rows * col;
	int currentIndex = 0;

	for (int boxNum = 0; boxNum < maxBox; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	Mesh mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

Mesh Vishv::Graphics::Meshbuilder::CreateCylinder(int rows, int col, float radius, float thicknessRow, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");


	//Make Random Numbers for all colors
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 2;
	}

	//create vertices
	std::vector<Vertex> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(0.0f, 0.0f, 0.0f);
	start.y = 0.0f - ((float)rows * 0.5f);

	const float deltaAngle = (360.0f / static_cast<float>(col)) * Math::Constans::DegToRad;

	//In the last vertex for for every row(col) is not complete circle

	//Set The vertices for the cylender
	for (int i = 0; i <= rows; ++i)
	{
		float currentAngle = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngle) * radius;	//sin theta
			vertices[index].position.x = cosf(currentAngle) * radius;	//cos theta
			vertices[index].position.y = (i * thicknessRow) + start.y;				//Affected by row

			currentAngle -= deltaAngle;

			//Setting UV
			vertices[index].texCoord.x = static_cast<float>(j) / (col);
			vertices[index].texCoord.y = static_cast<float>(i) / (rows);

			//setting Normal
			vertices[index].normal = { vertices[index].position.x, 0.0f, vertices[index].position.z };
			vertices[index].normal.Normalize();

			//setting Tangent
			vertices[index].tangent = Math::Vector3(-vertices[index].position.z, 0.0f, vertices[index].position.x);
			if (vertices[index].tangent.MagnitudeSq() != 0.0f)
				vertices[index].tangent.Normalize();
		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = (rows * thicknessRow)  * 0.5f;

		vertices[numVertices - 2].normal = { 0.0f, -1.0f, 0.0f };
		vertices[numVertices - 1].normal = { 0.0f, 1.0f, 0.0f };
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		//vertices[i].color = { dist(mt), dist(mt), dist(mt), 1.0f };
	}


	int numIndices = ((rows * col) * 2) * 3;

	if (capped)
	{
		//indices for the triangle fan
		numIndices += (col * 2) * 3;
	}

	std::vector<uint32_t> indices;
	indices.resize(numIndices);
	int currentRow = 0, currentColumn = 0;

	int currentIndex = 0;

	for (int boxNum = 0; boxNum < rows * col; ++boxNum)
	{
		indices[currentIndex] = boxNum + (boxNum / col);
		indices[currentIndex + 1] = boxNum + (boxNum / col) + 1;
		indices[currentIndex + 2] = indices[currentIndex] + col + 1;

		indices[currentIndex + 3] = boxNum + (boxNum / col) + 1;;
		indices[currentIndex + 4] = indices[currentIndex + 1] + col + 1;
		indices[currentIndex + 5] = indices[currentIndex] + col + 1;

		currentIndex += 6;
	}

	if (capped)
	{
		//make triangle fan
		//on top and buttom

		//buttom
		for (int triNum = 0; triNum < col; ++triNum)
		{
			indices[currentIndex] = triNum;
			indices[currentIndex + 1] = numVertices - 2;
			indices[currentIndex + 2] = triNum + ((triNum == col) ? 0 : 1);

			currentIndex += 3;
		}

		//top
		for (int triNum = numVertices - col - ((capped) ? 3 : 1); triNum < numVertices - ((capped) ? 3 : 1); ++triNum)
		{
			indices[currentIndex] = triNum + ((triNum == col - 1) ? 0 : 1);
			indices[currentIndex + 2] = triNum;
			indices[currentIndex + 1] = numVertices - 1;

			currentIndex += 3;
		}
	}


	Mesh mesh;

	mesh.mVertices = std::move(vertices);
	mesh.mIndices = std::move(indices);

	return mesh;
}

#pragma endregion Normal, Tangent, Texture

