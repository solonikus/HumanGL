

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdio.h>
#include "vector.hpp"
/*
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
*/
static float ToRadian(float angle)
{
    return angle * (M_PI / 180);
}

template <class T>
struct Matrix
{
    T member[4][4];

    Matrix() {};

    Matrix(T a)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                member[i][j] = a;
        }
    }

    Matrix(T a, int b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                member[i][j] = 0;
        }
        if (b == 1)
        {
            member[0][0] = a;
            member[1][1] = a;
            member[2][2] = a;
            member[3][3] = a;
        }
    }

    Matrix(const Matrix &a)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->member[i][j] = a.member[i][j];
            }
        }
    }

    T *operator [] (int i) {return this->member[i];}

    Matrix operator* (Vector4<T> &b)
    {
        Matrix<T> c(0);
        T d[4] = {b.x, b.y, b.z, b.w};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c[i][j] = this->member[i][j] * d[j];
            }
        }
        return c;
    }

    Matrix operator* (T b)
    {
        Matrix<T> c(0);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c[i][j] = this->member[i][j] * b;
            }
        }
        return c;
    }

    
    Matrix operator* (Matrix &b)
    {
        Matrix<T> c(0);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    c[i][j] += this->member[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

    Matrix operator+ (Matrix &a)
    {
        Matrix<T> c(0);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c[i][j] = this->member[i][j] + a.member[i][j];
            }
        }
		return c;
    }

    Matrix Transp()
    {
        Matrix<T> c(0.0);
        for(int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                c.member[i][j] = this->member[j][i];
            }
        }
        return c;
    }

    Matrix ToScale(Vector3<T> &b)
    {
        Matrix<T> c(*this);
        c[0][0] = this->member[0][0] * b.x;
        c[1][1] = this->member[1][1] * b.y;
        c[2][2] = this->member[2][2] * b.z;
        return c;
    }

    Matrix Translate(Vector4<T> &b)
    {
        Matrix<T> c(*this);
		c[0][3] = this->member[0][3] + b.x;
		c[1][3] = this->member[1][3] + b.y;
		c[2][3] = this->member[2][3] + b.z;
		c[3][3] = this->member[3][3] + b.w;
        return c;
    }

    Matrix Translate(T x, T y, T z)
    {
        Matrix<T> c(*this);
        c[3][0] = this->member[3][0] + x;
        c[3][1] = this->member[3][1] + y;
        c[3][2] = this->member[3][2] + z;
        c[3][3] = static_cast<T>(1);
        return c;
    }

    Matrix Translate(Vector3<T> &b)
    {
        Matrix<T> c(*this);
        T x, y, z;
        x = b.x;
        y = b.y;
        z = b.z;
        c = c.Translate(x, y, z);
        return c;
    }

    static Matrix RotateMatrix(T x, T y, T z, T w)
    {
        Matrix<T> m(0.0);

        T xx = x * x;
        T xy = x * y;
        T xz = x * z;
        T xw = x * w;
        T yy = y * y;
        T yz = y * z;
        T yw = y * w;
        T zz = z * z;
        T zw = z * w;

        m[0][0] = 1 - 2 * (yy + zz);
        m[1][0] = 2 * (xy - zw);
        m[2][0] = 2 * (xz + yw);
        m[0][1] = 2 * (xy + zw);
        m[1][1] = 1 - 2 * (xx + zz);
        m[2][1] = 2 * (yz - xw);
        m[0][2] = 2 * (xz - yw);
        m[1][2] = 2 * (yz + xw);
        m[2][2] = 1 - 2 * (xx + yy);
        m[3][3] = 1;
        return m;
    }

    Matrix Rotate(float angle, Vector3<T> v)
    {
        Matrix<T> c(*this);
        Matrix<T> r;
        angle = ToRadian(angle);
        v = v.normalize();
        Vector4<T> quaternion(sin(angle/2) * v.x, sin(angle/2) * v.y, sin(angle/2) * v.z, cos(angle/2));
        r = RotateMatrix(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
        c = r * c;
        return c;
    }

    Matrix Rotate(float angle, T x, T y, T z)
    {
        Vector3<T> vec(x,y,z);
        return this->Rotate(angle, vec);
    }

    Matrix Rotate(Vector4<T> quaternion)
    {
        Matrix<T> c(*this);
        Matrix<T> r;
        r = RotateMatrix(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
        c = r * c;
        return c;
    }

    Vector4<T> RotateMatrixToQuaternion()
    {
        float      tr, s, q[4];
        int        i, j, k;
        Vector4<T> quat;
        Matrix<T>  m(*this);

        int nxt[3] = {1, 2, 0};
        tr = m[0][0] + m[1][1] + m[2][2];
        if (tr > 0.0)
        {
            s = sqrt(tr + 1.0);
            quat.w = s / 2.0;
            s = 0.5 / s;
            quat.x = (m[1][2] - m[2][1]) * s;
            quat.y = (m[2][0] - m[0][2]) * s;
            quat.z = (m[0][1] - m[1][0]) * s;
        }
        else
        {
            i = 0;
            if (m[1][1] > m[0][0]) i = 1;
            if (m[2][2] > m[i][i]) i = 2;
            j = nxt[i];
            k = nxt[j];
            s = sqrt ((m[i][i] - (m[j][j] + m[k][k])) + 1.0);
            q[i] = s * 0.5;
            if (s != 0.0) s = 0.5 / s;
            q[3] = (m[j][k] - m[k][j]) * s;
            q[j] = (m[i][j] + m[j][i]) * s;
            q[k] = (m[i][k] + m[k][i]) * s;
            quat.x = q[0];
            quat.y = q[1];
            quat.z = q[2];
            quat.w = q[3];
        }
         return quat;
    }

    Matrix Perspective(T fov, T width, T height, T near, T far)
    {
        T D2R = M_PI / 180.0;
        T yScale = 1 / tan(0.5f * fov * D2R);
        T aspect = width / height;
        T nearmfar = near - far;
        T tanHalfFovy = tan(ToRadian(fov) / static_cast<T>(2));
    
        member[0][0] = 1.0 / (aspect * tanHalfFovy);
        member[0][1] = 0.0f;
        member[0][2] = 0.0f;
        member[0][3] = 0.0f;
    
        member[1][0] = 0.0f;
        member[1][1] = yScale;
        member[1][2] = 0.0f;
        member[1][3] = 0.0f;
    
        member[2][0] = 0.0f;
        member[2][1] = 0.0f;
        member[2][2] = -(far + near) / (far - near);
        member[2][3] = -1.0f;
    
        member[3][0] = 0.0f;
        member[3][1] = 0.0f;
        member[3][2] = 2 * far * near / nearmfar;
        member[3][3] = 0.0f;
        return *this;
    }

    Vector3<T> TranslateToVector3()
    {
        Vector3<T> v(0);
        v.x = member[0][3];
        v.y = member[1][3];
        v.z = member[2][3];
        return v;
    }

    Vector3<T> ScaleToVector3()
    {
        Vector3<T> v(0);
        v.x = member[0][0];
        v.y = member[1][1];
        v.z = member[2][2];
        return v;
    }
};
/*
static void printmatrix(glm::mat4 m)
{
	printf("glu:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

static void printmatrix(Matrix<float> m)
{
	printf("nonglu:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
*/
#endif
