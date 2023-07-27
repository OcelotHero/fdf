/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transforms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:47:43 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:47:43 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * Scales the given matrix with the given scaling vector. Returns a new
 * transformation matrix with the matrix transformation applied.
 *
 * @param	mat	The matrix to transform
 * @param	vec	The homogeneous scaling vector to apply to the given matrix
 * @return	The resulting transformation matrix
 */
t_mat4	scale(t_mat4 mat, t_vec4 vec)
{
	return ((t_mat4){{
			{{mat.e[0].e[0] * vec.x,
					mat.e[0].e[1] * vec.y,
					mat.e[0].e[2] * vec.z,
					mat.e[0].e[3]}},
			{{mat.e[1].e[0] * vec.x,
					mat.e[1].e[1] * vec.y,
					mat.e[1].e[2] * vec.z,
					mat.e[1].e[3]}},
			{{mat.e[2].e[0] * vec.x,
					mat.e[2].e[1] * vec.y,
					mat.e[2].e[2] * vec.z,
					mat.e[2].e[3]}},
			{{0.0f, 0.0f, 0.0f, 1.0f}}}});
}

/**
 * Translates the given matrix with the given translation vector. Returns a new
 * transformation matrix with the matrix transformation applied.
 *
 * @param	mat	The matrix to transform
 * @param	vec	The homogeneous translation vector to apply to the given matrix
 * @return	The resulting transformation matrix
 */
t_mat4	translate(t_mat4 mat, t_vec4 vec)
{
	return ((t_mat4){{
			{{mat.e[0].e[0], mat.e[0].e[1], mat.e[0].e[2],
					mat.e[0].e[0] * vec.x + mat.e[0].e[1] * vec.y
					+ mat.e[0].e[2] * vec.z + mat.e[0].e[3]}},
			{{mat.e[1].e[0], mat.e[1].e[1], mat.e[1].e[2],
					mat.e[1].e[0] * vec.x + mat.e[1].e[1] * vec.y
					+ mat.e[1].e[2] * vec.z + mat.e[1].e[3]}},
			{{mat.e[2].e[0], mat.e[2].e[1], mat.e[2].e[2],
					mat.e[2].e[0] * vec.x + mat.e[2].e[1] * vec.y
					+ mat.e[2].e[2] * vec.z + mat.e[2].e[3]}},
			{{0.0f, 0.0f, 0.0f, 1.0f}}}});
}

/**
 * Creates a Rodrigues' rotation matrix and multiplies it with the given matrix.
 * Returns a new transformation matrix with the matrix transformation applied.
 *
 * @param	mat	The matrix to transform
 * @param	rad	The rotation angle, given in radians
 * @param	vec	The homogeneous rotation vector
 * @return	The resulting transformation matrix
 */
t_mat4	rotate(t_mat4 mat, float rad, t_vec4 vec)
{
	float	s;
	float	c;
	t_mat4	res;

	s = sin(rad);
	c = cos(rad);
	res = ((t_mat4){{
		{{c + pow(vec.x, 2) * (1.0f - c),
			vec.x * vec.y * (1.0f - c) - vec.z * s,
			vec.x * vec.z * (1.0f - c) + vec.y * s,
			0.0f}},
		{{vec.y * vec.x * (1.0f - c) + vec.z * s,
			c + pow(vec.y, 2) * (1.0f - c),
			vec.y * vec.z * (1.0f - c) - vec.x * s,
			0.0f}},
		{{vec.z * vec.x * (1.0f - c) - vec.y * s,
			vec.z * vec.y * (1.0f - c) + vec.x * s,
			c + pow(vec.z, 2) * (1.0f - c),
			0.0f}},
		{{0.0f, 0.0f, 0.0f, 1.0f}}}});
	return (mat_mat(mat, res));
}
