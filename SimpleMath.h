#ifndef _S_MATH_H_
#define _S_MATH_H_

//RGB color with Alfa
struct Color4f
{
	union
	{
		struct RGBColor
		{
			float r, g, b, a;
		} RGB;
		float C[4];
	};

	Color4f& operator = (const Color4f &right)
	{
		C[0] = right.C[0];
		C[1] = right.C[1];
		C[2] = right.C[2];
		C[3] = right.C[3];
		return *this;
	}

	bool operator == (const Color4f &right)
	{
		return ((C[0] = right.C[0]) &&
			(C[1] = right.C[1]) &&
			(C[3] = right.C[3]) &&
			(C[2] = right.C[2]));
	}

	bool operator != (const Color4f &right)
	{
		return ((C[0] != right.C[0]) ||
			(C[1] != right.C[1]) ||
			(C[3] != right.C[3]) ||
			(C[2] != right.C[2]));
	}

	Color4f(float r, float g, float b, float a)
	{
		RGB.r = r; RGB.g = g; RGB.b = b; RGB.a = a;
	}

	Color4f()
	{
		RGB.r = 0; RGB.g = 0; RGB.b = 0; RGB.a = 0;
	}

};

//2d vector
struct Vector3f
{
	union
	{
		struct SimpleVector3f
		{
			float x, y;
		} Vector;
		float V[2];
	};

	Vector3f()
	{
		Vector.x = 0.0f;
		Vector.y = 0.0f;
	}

	Vector3f(float InX, float InY, float InZ)
	{
		Vector.x = InX;
		Vector.y = InY;
	}

	Vector3f(const Vector3f &Other)
	{
		Vector.x = Other.Vector.x;
		Vector.y = Other.Vector.y;
	}

	Vector3f operator + (const Vector3f &Other)
	{
		return Vector3f(V[0] + Other.V[0], V[1] + Other.V[1], V[2] + Other.V[2]);
	}

	Vector3f& operator += (const Vector3f &Other)
	{
		Vector.x += Other.Vector.x;
		Vector.y += Other.Vector.y;
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
		return *this;
	}
};

#endif