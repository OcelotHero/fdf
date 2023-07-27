/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_initializers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:41:43 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 06:36:19 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * Returns a 4x4 null matrix.
 *
 * @return	A 4x4 null matrix
 */
t_mat4	zeros(void)
{
	return ((t_mat4){{
			{{0.0f, 0.0f, 0.0f, 0.0f}},
			{{0.0f, 0.0f, 0.0f, 0.0f}},
			{{0.0f, 0.0f, 0.0f, 0.0f}},
			{{0.0f, 0.0f, 0.0f, 0.0f}}}});
}

/**
 * Returns a 4x4 identity matrix.
 *
 * @return	A 4x4 identity matrix
 */
t_mat4	eye(void)
{
	return ((t_mat4){{
			{{1.0f, 0.0f, 0.0f, 0.0f}},
			{{0.0f, 1.0f, 0.0f, 0.0f}},
			{{0.0f, 0.0f, 1.0f, 0.0f}},
			{{0.0f, 0.0f, 0.0f, 1.0f}}}});
}

/**
 * Returns a 4x4 diagonal matrix with the given input as diagonal entries.
 *
 * @param	vec	Input for the main diagonal entries
 * @return	A 4x4 diagonal matrix
 */
t_mat4	diag(t_vec4 vec)
{
	return ((t_mat4){{
			{{vec.x, 0.0f, 0.0f, 0.0f}},
			{{0.0f, vec.y, 0.0f, 0.0f}},
			{{0.0f, 0.0f, vec.z, 0.0f}},
			{{0.0f, 0.0f, 0.0f, vec.w}}}});
}
