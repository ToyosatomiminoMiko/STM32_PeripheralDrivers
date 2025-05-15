#ifndef BSP_MATRIX_MATRIX_H_
#define BSP_MATRIX_MATRIX_H_
#include "main.h"
#include <math.h>
#include <string.h>

typedef float_t Matrix_4x4[4][4];
typedef float_t Vector_4[4];
typedef Vector_4 box[8];

void
matrix_multiply_4x4(Matrix_4x4 result, const Matrix_4x4 a, const Matrix_4x4 b);
void
matrix_vector_multiply(Vector_4 result, const Matrix_4x4 mat,
		const Vector_4 vec);

void
translate_3d(Matrix_4x4 result_0, float_t const tx, float_t const ty,
		float_t const tz);
void
rotate_x_3d(Matrix_4x4 result_0, float_t theta);
void
rotate_y_3d(Matrix_4x4 result_0, float_t theta);
void
rotate_z_3d(Matrix_4x4 result_0, float_t theta);
void
scale_3d(Matrix_4x4 result_0, float_t sx, float_t sy, float_t sz);

#endif /* BSP_MATRIX_MATRIX_H_ */
