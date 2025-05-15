#include "matrix.h"

void matrix_multiply_4x4(Matrix_4x4 result, const Matrix_4x4 a,
		const Matrix_4x4 b)
{
	Matrix_4x4 tmp;
	for (uint8_t i = 0; i < 4; ++i)
	{
		for (uint8_t j = 0; j < 4; ++j)
		{
			float_t sum = 0;
			for (uint8_t k = 0; k < 4; ++k)
			{
				sum += a[i][k] * b[k][j];
			}
			tmp[i][j] = sum;
		}
	}
	memcpy(result, tmp, sizeof(Matrix_4x4));
}

void matrix_vector_multiply(Vector_4 result, const Matrix_4x4 matrix,
		const Vector_4 vector)
{
	Vector_4 tmp;
	for (uint8_t i = 0; i < 4; ++i)
	{
		tmp[i] = 0;
		for (uint8_t k = 0; k < 4; ++k)
		{
			tmp[i] += matrix[i][k] * vector[k];
		}
	}
	memcpy(result, tmp, sizeof(Vector_4));
}

void translate_3d(Matrix_4x4 homogeneous, float_t const tx, float_t const ty,
		float_t const tz)
{
	Matrix_4x4 rx =
	{
	{ 1, 0, 0, tx },
	{ 0, 1, 0, ty },
	{ 0, 0, 1, tz },
	{ 0, 0, 0, 1 } };
	memcpy(homogeneous, rx, sizeof(Matrix_4x4));
}

void rotate_x_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	Matrix_4x4 rx =
	{
	{ 1, 0, 0, 0 },
	{ 0, c, -s, 0 },
	{ 0, s, c, 0 },
	{ 0, 0, 0, 1 } };
	memcpy(homogeneous, rx, sizeof(Matrix_4x4));
}

void rotate_y_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	Matrix_4x4 rx =
	{
	{ c, 0, s, 0 },
	{ 0, 1, 0, 0 },
	{ -s, 0, c, 0 },
	{ 0, 0, 0, 1 } };
	memcpy(homogeneous, rx, sizeof(Matrix_4x4));
}

void rotate_z_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	Matrix_4x4 rx =
	{
	{ c, -s, 0, 0 },
	{ s, c, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 } };
	memcpy(homogeneous, rx, sizeof(Matrix_4x4));
}

void scale_3d(Matrix_4x4 homogeneous, float_t sx, float_t sy, float_t sz)
{
	Matrix_4x4 rx =
	{
	{ sx, 0, 0, 0 },
	{ 0, sy, 0, 0 },
	{ 0, 0, sz, 0 },
	{ 0, 0, 0, 1 } };
	memcpy(homogeneous, rx, sizeof(Matrix_4x4));
}

