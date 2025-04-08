#include "matrix.h"

void matrix_multiply_4x4(Matrix_4x4 result, const Matrix_4x4 a,
		const Matrix_4x4 b)
{
	for (uint8_t x = 0; x < 4; x++) // 遍历结果矩阵的行
		for (uint8_t y = 0; y < 4; y++) // 遍历结果矩阵的列
			result[x][y] = a[x][0] * b[0][y] + a[x][1] * b[1][y]
					+ a[x][2] * b[2][y] + a[x][3] * b[3][y];
}

void matrix_vector_multiply(Vector_4 result, const Matrix_4x4 mat,
		const Vector_4 vec)
{
	for (uint8_t i = 0; i < 4; i++) // 遍历结果向量的每个分量
		result[i] = mat[i][0] * vec[0] + mat[i][1] * vec[1] + mat[i][2] * vec[2]
				+ mat[i][3] * vec[3];
}

void translate_3d(Matrix_4x4 homogeneous, float_t const tx, float_t const ty,
		float_t const tz)
{
	homogeneous[0][3] = tx;
	homogeneous[1][3] = ty;
	homogeneous[2][3] = ty;
}

void rotate_x_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	homogeneous[1][1] = c;
	homogeneous[1][2] = -s;
	homogeneous[2][1] = s;
	homogeneous[2][2] = c;
}

void rotate_y_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	homogeneous[0][0] = c;
	homogeneous[0][2] = s;
	homogeneous[2][0] = -s;
	homogeneous[2][2] = c;
}

void rotate_z_3d(Matrix_4x4 homogeneous, float_t theta)
{
	float c = cos(theta);
	float s = sin(theta);
	homogeneous[0][0] = c;
	homogeneous[0][1] = -s;
	homogeneous[1][0] = s;
	homogeneous[1][1] = c;
}

void scale_3d(Matrix_4x4 homogeneous, float_t sx, float_t sy, float_t sz)
{
	homogeneous[0][0] = sx;
	homogeneous[1][1] = sy;
	homogeneous[2][2] = sz;
}

