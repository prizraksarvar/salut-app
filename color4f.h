//
// Sarvar Khasanov
//

#ifndef SALUTAPP_COLOR4F_H_
#define SALUTAPP_COLOR4F_H_

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
		RGB.r = 0; 
		RGB.g = 0;
		RGB.b = 0;
		RGB.a = 0;
	}
};

#endif