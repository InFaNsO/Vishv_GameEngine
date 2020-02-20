#include "Precompiled.h"
#include "SimpleDraw.h"

#include "ConstantBuffer.h"
#include "GraphicsSystem.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"
#include "MeshBuffer.h"

#include "EffectsManager.h"

using namespace Vishv;
using namespace Vishv::Graphics;

namespace
{
	//Private impimentation
	class SimpleDrawImplementation
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();
		void Render(const Camera& camera);

		void AddLine(const Math::Vector3 & v0, const Math::Vector3 & v1, const Color & color);
		void AddLine(const VertexPC& v0, const VertexPC& v1);

	private:
		using ShaderBuffer = Vishv::Graphics::TypedConstantBuffer<Vishv::Math::Matrix4>;
		ShaderBuffer mShaderBuffer;
		MeshBuffer mMeshBuffer;

		std::vector<VertexPC> mVertices;

		bool mInitialize{ false };
	};

	void SimpleDrawImplementation::Initialize(uint32_t maxVertexCount)
	{
		VISHVASSERT(!mInitialize, "[SimpleDrawImpl] Already Initialized.\n");

		EffectsManager::Get()->AddEffect(EffectType::SimpleDraw);
		mShaderBuffer.Initialize();
		mMeshBuffer.Initialize(maxVertexCount, sizeof(VertexPC), nullptr, true);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mVertices.reserve(maxVertexCount);

		mInitialize = true;
	}

	void SimpleDrawImplementation::Terminate()
	{
		VISHVASSERT(mInitialize, "[SimpleDrawImpl] Already Terminated.\n");
		mShaderBuffer.Terminate();
		mMeshBuffer.Terminate();

		mInitialize = false;
	}

	void SimpleDrawImplementation::Render(const Camera & camera)
	{
		VISHVASSERT(mInitialize, "[SimpleDrawImpl] Not Initialized.\n");

		const Math::Matrix4& matView = camera.GetViewMatrix();
		const Math::Matrix4& matProj = camera.GetPerspectiveMatrix();

		EffectsManager::Get()->BindEffect(EffectType::SimpleDraw);

		auto transform = Math::Matrix4::Transpose(matView * matProj);

		EffectsManager::Get()->GetBufferData(EffectType::SimpleDraw)->GetTextureing()->wvp = transform;
		EffectsManager::Get()->Set(EffectType::SimpleDraw);
		EffectsManager::Get()->BindBuffer(EffectType::SimpleDraw);

		mMeshBuffer.Update((int)mVertices.size(), mVertices.data());

		mMeshBuffer.Render();

		mVertices.clear();
	}

	void SimpleDrawImplementation::AddLine(const Math::Vector3 & v0, const Math::Vector3 & v1, const Color & color)
	{
		VISHVASSERT(mInitialize, "[SimpleDrawImpl::AddLine] not initialized");
		if (mVertices.size() + 2 <= mVertices.capacity())
		{
			mVertices.emplace_back(v0, color);
			mVertices.emplace_back(v1, color);
		}
	}

	void SimpleDrawImplementation::AddLine(const VertexPC & v0, const VertexPC & v1)
	{
		VISHVASSERT(mInitialize, "[SimpleDrawImpl::AddLine] not initialized");
		if (mVertices.size() + 2 <= mVertices.capacity())
		{
			mVertices.emplace_back(v0);
			mVertices.emplace_back(v1);
		}
	}

	std::unique_ptr<SimpleDrawImplementation> sInstance;
}


void Vishv::Graphics::SimpleDraw::StaticInitialize(uint32_t maxVertex)
{
	sInstance = std::make_unique<SimpleDrawImplementation>();
	sInstance->Initialize(maxVertex);
}

void Vishv::Graphics::SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void Vishv::Graphics::SimpleDraw::AddLine(const Math::Vector3 & v0, const Math::Vector3 & v1, const Color & color)
{
	sInstance->AddLine(v0, v1, color);
}

void Vishv::Graphics::SimpleDraw::AddLine(const VertexPC & v0, const VertexPC & v1)
{
	sInstance->AddLine(v0, v1);
}

inline int GenerateIndex(int row, int col, int maxCol)
{
	return (row * (maxCol)) + col;
}

void Vishv::Graphics::SimpleDraw::AddSphere(const Math::Vector3& center, const float radius, const Vishv::Graphics::Color & color, int row, int col)
{
	//create vertices
	std::vector<VertexPC> vertices;

	int numVertices = (row + 1) * (col + 1);

	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(center);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(row);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float currentY = center.y - radius;

	bool half = false;

	//Set The vertices for the sphere
	for (int i = 0; i <= row; ++i)
	{
		float currentAngleX = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngleX) * currentRadius + start.z;	//sin theta
			vertices[index].position.x = cosf(currentAngleX) * currentRadius + start.x;	//cos theta
			vertices[index].position.y = currentY;							//Affected by row

			currentAngleX -= deltaAngleX;

		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) half = true;



		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = radius * sinf(currentAngleY);

		currentY = (((cosf(currentAngleY) * radius) + (half ? radius : -radius)) * (half ? 1.0f : -1.0f)) + (center.y - radius);
	}

	//Set Color
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j <= col; ++j)
		{
			vertices[GenerateIndex(i, j, col + 1)].color = color;
		}
	}

	MakeLine(vertices, row + 1, col + 1);

}
void Vishv::Graphics::SimpleDraw::AddCylinder(const Math::Vector3& center, float radius, float height, const Vishv::Graphics::Color& color, int rows)
{
	AddCylinder(center, color, radius, rows, 6, height / rows, false);
}
void Vishv::Graphics::SimpleDraw::AddCylinder(const Math::Vector3 & center, const Vishv::Graphics::Color & color, float radius, int rows, int col, float rowThickness, bool capped)
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
	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(center);
	start.y = center.y - ((rows * rowThickness) * 0.5f);


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
			vertices[index].position.y = start.y + i * rowThickness;				//Affected by row

			currentAngle -= deltaAngle;

		}
	}
	if (capped)
	{
		//set the center points for top and buttom
		vertices[numVertices - 2].position = start;		//buttom peice
		vertices[numVertices - 1].position = start;		//Top peice
		vertices[numVertices - 1].position.y = rows * rowThickness;
	}

	//Set Color
	for (int i = 0; i < numVertices; ++i)
	{
		vertices[i].color = color;
	}

	MakeLine(vertices, rows, col);
}

void Vishv::Graphics::SimpleDraw::AddScreen(const Math::Vector2 & center, const float radius, const Vishv::Graphics::Color & color)
{
	
}

void Vishv::Graphics::SimpleDraw::AddCube(const Math::Vector3& center, float lx, const Vishv::Graphics::Color& color)
{
	AddCuboid(center, lx, lx, lx, color);
}


void Vishv::Graphics::SimpleDraw::AddCuboid(const Math::Vector3& center, float lx, float ly, float lz, const Vishv::Graphics::Color& color)
{
	Math::Shapes::Cuboid c;
	c.mTransform.mPosition = center;
	c.SetLengthX(lx);
	c.SetLengthY(ly);
	c.SetLengthZ(lz);

	AddCuboid(c, color);
}

void Vishv::Graphics::SimpleDraw::AddCuboid(const Math::Shapes::Cuboid & cuboid, const Vishv::Graphics::Color & color)
{
	float hX = cuboid.GetLengthX() * 0.5f;
	float hY = cuboid.GetLengthY() * 0.5f;
	float hZ = cuboid.GetLengthZ() * 0.5f;

	Math::Vector3 bfl, bfr, bbl, bbr, tbr, tbl, tfr, tfl;
	
	Math::Vector3 cPos = cuboid.mTransform.Position();
	
	bfl.x = cPos.x - hX;
	bfl.y = cPos.y - hY;
	bfl.z = cPos.z - hZ;

	tbr.x = cPos.x + hX;
	tbr.y = cPos.y + hY;
	tbr.z = cPos.z + hZ;

	bbl.x = bfl.x;
	bbl.y = bfl.y;
	bbl.z = tbr.z;

	bfr.x = tbr.x;
	bfr.y = bfl.y;
	bfr.z = bfl.z;

	bbr.x = tbr.x;
	bbr.y = bfl.y;
	bbr.z = tbr.z;

	tbl.x = bfl.x;
	tbl.y = tbr.y;
	tbl.z = tbr.z;

	tfl.x = bfl.x;
	tfl.y = tbr.y;
	tfl.z = bfl.z;

	tfr.x = tbr.x;
	tfr.y = tbr.y;
	tfr.z = bfl.z;


	//For Rotation around local
	bfl = ((bfl - cPos) * cuboid.mTransform.Rotation()) + cPos;
	bbl = ((bbl - cPos) * cuboid.mTransform.Rotation()) + cPos;
	bfr = ((bfr - cPos) * cuboid.mTransform.Rotation()) + cPos;
	bbr = ((bbr - cPos) * cuboid.mTransform.Rotation()) + cPos;
	
	tfl = ((tfl - cPos) * cuboid.mTransform.Rotation()) + cPos;
	tbl = ((tbl - cPos) * cuboid.mTransform.Rotation()) + cPos;
	tfr = ((tfr - cPos) * cuboid.mTransform.Rotation()) + cPos;
	tbr = ((tbr - cPos) * cuboid.mTransform.Rotation()) + cPos;


	AddLine(bfl, bfr, color);
	AddLine(bbl, bbr, color);

	AddLine(bfl, bbl, color);
	AddLine(bfr, bbr, color);

	AddLine(tfl, tfr, color);
	AddLine(tbl, tbr, color);

	AddLine(tfl, tbl, color);
	AddLine(tfr, tbr, color);

	AddLine(bfl, tfl, color);
	AddLine(bbl, tbl, color);
	AddLine(bfr, tfr, color);
	AddLine(bbr, tbr, color);
}

void Vishv::Graphics::SimpleDraw::AddCapsule(const Math::Shapes::Capsule & capsule, const Vishv::Graphics::Color & color)
{
	int col = 6;
	int row = 3;
	//AddCylinder(capPos, color, capsule.mRadius, 2, col, capsule.GetHeight(), false);
	//create vertices
	std::vector<VertexPC> vertices;

	Math::Vector3 capPos = capsule.mTransform.mPosition;

	int numVertices = (row + 1) * (col + 1);

	vertices.resize(numVertices);

	//Set the top left corner at origin
	Math::Vector3 start(capPos);

	const float deltaAngleY = Math::Constans::Pi / static_cast<float>(row);
	const float deltaAngleX = Math::Constans::TwoPi / static_cast<float>(col);


	//In the last vertex for for every row(col) is not complete circle
	float currentRadius = 0.0f;
	float currentAngleY = 0.0f;
	float currentY = capPos.y - capsule.mRadius - (capsule.GetHeight() * 0.5f);

	bool half = false;
	bool increased = false;

	//Set The vertices for the sphere
	for (int i = 0; i <= row; ++i)
	{
		float currentAngleX = Math::Constans::TwoPi;
		//Set the plane coordinates along +x and -y
		for (int j = 0; j <= col; ++j)
		{
			//Set x,y,z for all the points in one row
			int index = j + (i * (col + 1));

			vertices[index].position.z = sinf(currentAngleX) * currentRadius + start.z;	//sin theta
			vertices[index].position.x = cosf(currentAngleX) * currentRadius + start.x;	//cos theta
			vertices[index].position.y = currentY;							//Affected by row

			currentAngleX -= deltaAngleX;

		}

		if (!half && ((i + 1) * deltaAngleY * Math::Constans::RadToDeg) > 90.0f) half = true;



		currentAngleY = (((i + 1) * deltaAngleY) - (half ? -Math::Constans::Pi : 0.0f)) * (half ? -1.0f : 1.0f);
		currentRadius = capsule.mRadius * sinf(currentAngleY);

		currentY = (((cosf(currentAngleY) * capsule.mRadius) + (half ? capsule.mRadius : -capsule.mRadius)) * (half ? 1.0f : -1.0f)) + (capPos.y - capsule.mRadius) + (half ? capsule.GetHeight() : 0.0f);
	}

	//Set Color
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j <= col; ++j)
		{
			vertices[GenerateIndex(i, j, col + 1)].color = color;
			//vertices[GenerateIndex(i, j, col + 1)].position *=  capsule.mTransform.Rotation();
		}
	}

	MakeLine(vertices, row + 1, col + 1);
}

inline void Vishv::Graphics::SimpleDraw::MakeLine(const std::vector<VertexPC>& vertices, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if(i > 0)
				AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i-1, j, col)]);
			//else
			//	AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(row, j)]);

			if(i < row - 1)
				AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i + 1, j, col)]);
			//else
			//	AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(0, j)]);
				
			if (j > 0)
				AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i, j - 1, col)]);
			//else
			//	AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i, col)]);


			if(j < col - 1)
				AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i, j + 1, col)]);
			//else
			//	AddLine(vertices[GenerateIndex(i, j, col)], vertices[GenerateIndex(i, 0)]);

		}
	}
}


void Vishv::Graphics::SimpleDraw::AddCone(const Math::Vector3 & start, Math::Vector3 & end, const Vishv::Graphics::Color & color, float radius, int rows, int col, bool capped)
{
	VISHVASSERT(rows >= 2, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few rows to generate a cylinder.");
	VISHVASSERT(col >= 3, "[Vishv::Graphics::Meshbuilder::CreateCylinder] To few columns to generate a cylinder.");

	Math::Vector3 direction = start - end;
	float height = direction.Magnitude();
	float thicknessRow = height / (rows - 1);

	int numVertices = (rows + 1) * (col + 1);

	if (capped)
	{
		numVertices += 1;
	}

	//create vertices
	std::vector<VertexPC> vertices;
	vertices.resize(numVertices);

	//Set the top left corner at origin
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
		vertices[i].color = color;
	}
	MakeLine(vertices, rows, col);
}

void Vishv::Graphics::SimpleDraw::AddSkeleton(const Skeleton & skeleton, const std::vector<Vishv::Math::Matrix4>& boneTransform)
{
	for (size_t i = 0; i < skeleton.bones.size(); ++i)
	{
		Vishv::Math::Matrix4 mat = boneTransform[i];

		Vishv::Graphics::SimpleDraw::AddSphere({ mat._41, mat._42, mat._43 }, 3.0f, skeleton.bones[i]->mDebugColor, 4, 4);
		for (size_t j = 0; j < skeleton.bones[i]->children.size(); ++j)
		{
			Vishv::Math::Matrix4 matC;
			matC = boneTransform[skeleton.bones[i]->childIndicies[j]];

			Vishv::Graphics::SimpleDraw::AddLine(mat.GetTranslation(), matC.GetTranslation(), skeleton.bones[i]->mDebugColor);
		}
	}
}

void Vishv::Graphics::SimpleDraw::Render(const Camera & camera)
{
	sInstance->Render(camera);
}


