/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:46:18 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:46:18 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * Returns a matrix multiplication of the given 4x4 matrix and another 4x4
 * matrix.
 *
 * @param	A	The input matrix
 * @param	B	The input matrix
 * @return	The resulting 4x4 A*B matrix
 */
t_mat4	mat_mat(t_mat4 A, t_mat4 B)
{
	int		i;
	int		j;
	int		k;
	t_mat4	res;

	res = zeros();
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				res.e[i].e[j] += A.e[i].e[k] * B.e[k].e[j];
		}
	}
	return (res);
}

/**
 * Returns a matrix multiplication of the given 4x4 matrix and a column vector.
 *
 * @param	A	The input matrix
 * @param	b	The input vector
 * @return	The resulting A*b column vector
 */
t_vec4	mat_vec(t_mat4 A, t_vec4 b)
{
	int		i;
	int		j;
	t_vec4	res;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		res.e[i] = 0;
		while (++j < 4)
			res.e[i] += A.e[i].e[j] * b.e[j];
	}
	return (res);
}

/**
 * Returns a new matrix with the matrix entries transposed.
 *
 * @param	mat	The matrix to transpose
 * @return	The resulting 4x4 A^T matrix
 */
t_mat4	transpose(t_mat4 mat)
{
	return ((t_mat4){{
			{{mat.e[0].e[0], mat.e[1].e[0], mat.e[2].e[0], mat.e[3].e[0]}},
			{{mat.e[0].e[1], mat.e[1].e[1], mat.e[2].e[1], mat.e[3].e[1]}},
			{{mat.e[0].e[2], mat.e[1].e[2], mat.e[2].e[2], mat.e[3].e[2]}},
			{{mat.e[0].e[3], mat.e[1].e[3], mat.e[2].e[3], mat.e[3].e[3]}}}});
}
