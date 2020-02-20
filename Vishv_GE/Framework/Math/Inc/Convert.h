#ifndef INCLUDED_VISHV_MATH_CONVERT
#define INCLUDED_VISHV_MATH_CONVERT

namespace Vishv::Math
{
	struct Vector3;
	struct Vector4;
	struct Matrix4;
	struct Quaternion;
	class Transform;



class Convert
{
public:
	static Vector3 MatrixToPosition(Matrix4& matrix);
	static Quaternion MatrixToQuaternion(Matrix4& matrix);
	static Transform MatrixToTransform(Matrix4& matrix);

};
}

#endif // !INCLUDED_VISHV_MATH_CONVERT

