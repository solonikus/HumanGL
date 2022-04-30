

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

template <class T>
struct Vector3
{
    T x;
    T y;
    T z;

    Vector3() {};
    Vector3(T a)
    {
        for (int i = 0; i < 3; i++) // ?
        {
            x = y = z = a;
        }
    }
    Vector3(T a, T b, T c)
    {
        x = a;
        y = b;
        z = c;
    }

    Vector3 normalize()
    {
        Vector3<T> v;
        float inv_length = 1.0f / sqrt(x*x + y*y + z*z);
        v.x = this->x * inv_length;
        v.y = this->y * inv_length;
        v.z = this->z * inv_length;
        return v;
    }

	Vector3 operator+ (Vector3<T> a) // TODO test
	{
		Vector3<T> c(0);
		c.x = this->x + a.x;
		c.y = this->y + a.y;
		c.z = this->z + a.z;
		return c;
	}

	Vector3 operator* (float a) // TODO Test
	{
		Vector3<T> c(0);
		c.x = this->x * a;
		c.y = this->y * a;
		c.z = this->z * a;
		return c;
	}
};

template <class T>
struct Vector4
{
    T x;
    T y;
    T z;
    T w;

    Vector4() {};
    Vector4(T a)
    {
        x = y = z = w = a;
    }
    Vector4(T a, T b, T c, T d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
    Vector4 VectorToQuaternion(float angle, Vector4<T> v)
    {
        Vector4<T> quaternion(*this);
        quaternion.x = sin(angle/2) * v.x;
        quaternion.y = sin(angle/2) * v.y;
        quaternion.z = sin(angle/2) * v.z;
        quaternion.w = cos(angle/2);
        return quaternion;
    }
    Vector4 VectorToQuaternion(float angle, Vector3<T> v)
    {
        Vector4<T> quaternion(*this);
        quaternion.x = sin(angle/2) * v.x;
        quaternion.y = sin(angle/2) * v.y;
        quaternion.z = sin(angle/2) * v.z;
        quaternion.w = cos(angle/2);
        return quaternion;
    }
	Vector4 EulerToQuaternion(Vector3<T> euler)
	{
		Vector4<T> quaternion(*this);

		double cy = cos(euler.x * 0.5);
		double sy = sin(euler.x * 0.5);
		double cp = cos(euler.y * 0.5);
		double sp = sin(euler.y * 0.5);
		double cr = cos(euler.z * 0.5);
		double sr = sin(euler.z * 0.5);

		quaternion.x = sr * cp * cy - cr * sp * sy;
		quaternion.y = cr * sp * cy + sr * cp * sy;
		quaternion.z = cr * cp * sy - sr * sp * cy;
		quaternion.w = cr * cp * cy + sr * sp * sy;
		return quaternion;
	}
};

#endif
