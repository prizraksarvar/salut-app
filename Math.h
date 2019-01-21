#ifndef _MATH_H_
#define _MATH_H_

struct remColor4f
{
        union
        {
                struct RGBColor
                {
                        float r, g, b, a;
                } RGB;
                float C[4];
        };

        remColor4f& operator = (const remColor4f &right)
        {
                C[0] = right.C[0];
                C[1] = right.C[1];
                C[2] = right.C[2];
                C[3] = right.C[3];
                return *this;
        }

        bool operator == (const remColor4f &right)
        {
                return ((C[0] = right.C[0]) &&
                                (C[1] = right.C[1]) &&
                                (C[3] = right.C[3]) &&
                                (C[2] = right.C[2]));
        }

        bool operator != (const remColor4f &right)
        {
                return ((C[0] != right.C[0]) ||
                                (C[1] != right.C[1]) ||
                                (C[3] != right.C[3]) ||
                                (C[2] != right.C[2]));
        }

        // constructors
        remColor4f(float r, float g, float b, float a)
        {
                RGB.r = r; RGB.g = g; RGB.b = b; RGB.a = a;
        }

        remColor4f()
        {
                RGB.r = 0; RGB.g = 0; RGB.b = 0; RGB.a = 0;
        }

};

struct remVector3f
{
        union
        {
                struct Vector3f
                {
                        float x, y, z;
                } Vector;
                float V[3];
        };

    remVector3f()
        {
                Vector.x = 0.0f;
                Vector.y = 0.0f;
                Vector.z = 0.0f;
        }

    remVector3f(float InX, float InY, float InZ)
        {
                Vector.x = InX;
                Vector.y = InY;
                Vector.z = InZ;
        }

    remVector3f(const remVector3f &Other)
        {
                Vector.x = Other.Vector.x;
                Vector.y = Other.Vector.y;
                Vector.z = Other.Vector.z;
        }

    remVector3f operator + (const remVector3f &Other)
    {
            return remVector3f(V[0] + Other.V[0], V[1] + Other.V[1], V[2] + Other.V[2]);
    }

    remVector3f& operator += (const remVector3f &Other)
    {
            Vector.x += Other.Vector.x;
                        Vector.y += Other.Vector.y; 
                        Vector.z += Other.Vector.z;
                        return *this;
    }

    remVector3f operator * (const remVector3f &Other)
    {
            return remVector3f(V[0] * Other.V[0], V[1] * Other.V[1], V[2] * Other.V[2]);
    }

    remVector3f& operator *= (const remVector3f &Other)
    {
            Vector.x *= Other.Vector.x; 
                        Vector.y *= Other.Vector.y;
                        Vector.z *= Other.Vector.z;
                        return *this;
    }

        bool operator == (const remVector3f &Other)
        {
                return ((V[0] == Other.V[0]) && (V[1] == Other.V[1]) && (V[2] == Other.V[2]));
        }

    remVector3f operator - (const remVector3f &Other)
    {
            return remVector3f(V[0] - Other.V[0], V[1] - Other.V[1], V[2] - Other.V[2]);
    }

    remVector3f& operator -= (const remVector3f &Other)
    {
            Vector.x -= Other.Vector.x; 
                        Vector.y -= Other.Vector.y;
                        Vector.z -= Other.Vector.z;
                        return *this;
    }

    remVector3f operator / (const remVector3f &Other)
    {
            return remVector3f(V[0] / Other.V[0], V[1] / Other.V[1], V[2] / Other.V[2]);
    }

    remVector3f& operator /= (const remVector3f &Other)
    {
            Vector.x /= Other.Vector.x; 
                        Vector.y /= Other.Vector.y;
                        Vector.z /= Other.Vector.z;
                        return *this;
    }
};

#endif