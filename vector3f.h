//
// Sarvar Khasanov
//

#ifndef SALUTAPP_VECTOR2F_H_
#define SALUTAPP_VECTOR2F_H_

//2d vector
struct Vector3f
{
	union
	{
		struct SimpleVector3f
		{
			float x, y, z;
		} Vector;
		float V[3];
	};

	Vector3f()
	{
		Vector.x = 0.0f;
		Vector.y = 0.0f;
		Vector.z = 0.0f;
	}

	Vector3f(float InX, float InY, float InZ)
	{
		Vector.x = InX;
		Vector.y = InY;
		Vector.z = InZ;
	}

	Vector3f(const Vector3f &Other)
	{
		Vector.x = Other.Vector.x;
		Vector.y = Other.Vector.y;
		Vector.z = Other.Vector.z;
	}

	Vector3f operator + (const Vector3f &Other)
	{
		return Vector3f(V[0] + Other.V[0], V[1] + Other.V[1], V[2] + Other.V[2]);
	}

	Vector3f& operator += (const Vector3f &Other)
	{
		Vector.x += Other.Vector.x;
		Vector.y += Other.Vector.y;
		Vector.z += Other.Vector.z;
		return *this;
	}

	Vector3f operator * (const Vector3f &Other)
	{
		return Vector3f(V[0] * Other.V[0], V[1] * Other.V[1], V[2] * Other.V[2]);
	}

	Vector3f& operator *= (const Vector3f &Other)
	{
		Vector.x *= Other.Vector.x;
		Vector.y *= Other.Vector.y;
		Vector.z *= Other.Vector.z;
		return *this;
	}

	Vector3f& operator *= (const float op)
	{
		Vector.x *= op;
		Vector.y *= op;
		Vector.z *= op;
		return *this;
	}

	bool operator == (const Vector3f &Other)
	{
		return ((V[0] == Other.V[0]) && (V[1] == Other.V[1]) && (V[2] == Other.V[2]));
	}

	Vector3f operator - (const Vector3f &Other)
	{
		return Vector3f(V[0] - Other.V[0], V[1] - Other.V[1], V[2] - Other.V[2]);
	}

	Vector3f& operator -= (const Vector3f &Other)
	{
		Vector.x -= Other.Vector.x;
		Vector.y -= Other.Vector.y;
		Vector.z -= Other.Vector.z;
		return *this;
	}

	Vector3f operator / (const Vector3f &Other)
	{
		return Vector3f(V[0] / Other.V[0], V[1] / Other.V[1], V[2] / Other.V[2]);
	}

	Vector3f& operator /= (const Vector3f &Other)
	{
		Vector.x /= Other.Vector.x;
		Vector.y /= Other.Vector.y;
		Vector.z /= Other.Vector.z;
		return *this;
	}
};

#endif