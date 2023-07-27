/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_projections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:47:25 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:47:25 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/**
 * Returns an orthogonal projection matrix of a symmetrical frustrum. Any
 * vertices that lies outside the frustrum is clipped.
 *
 * @param	width	Frustrum width
 * @param	width	Frustrum height
 * @param	near	Frustrum near plane
 * @param	far		Frustrum far plane
 * @return	The orthogonal projection matrix
 */
t_mat4	ortho(float width, float height, float near, float far)
{
	return ((t_mat4){{
			{{2.0f / width, 0.0f, 0.0f, 0.0f}},
			{{0.0f, 2.0f / height, 0.0f, 0.0f}},
			{{0.0f, 0.0f, -2.0f / (far - near),
					-(far + near) / (far - near)}},
			{{0.0f, 0.0f, 0.0f, 1.0f}}}});
}

/**
 * Returns a perspective projection matrix of a symmetrical frustrum. Any
 * vertices that lies outside the frustrum is clipped.
 *
 * @param	fovy	Frustrum FoV in the vertical direction, given in radians
 * @param	aspect	Frustrum aspect ratio
 * @param	near	Frustrum near plane
 * @param	far		Frustrum far plane
 * @return	The perspective projection matrix
 */
t_mat4	perspective(float fovy, float aspect, float near, float far)
{
	float		tanhalf;

	tanhalf = tan(fovy / 2);
	return ((t_mat4){{
			{{1.0f / (aspect * tanhalf), 0.0f, 0.0f, 0.0f}},
			{{0.0f, 1.0f / tanhalf, 0.0f, 0.0f}},
			{{0.0f, 0.0f, -(far + near) / (far - near),
					-(2.0f * far * near) / (far - near)}},
			{{0.0f, 0.0f, -1.0f, 0.0f}}}});
}

/**
 * Returns a perspective projection matrix of an asymmetrical frustrum. Any
 * vertices that lies outside the frustrum is clipped.
 *
 * @param	hor		Frustrum left and right plane
 * @param	ver		Frustrum bottom and top plane
 * @param	near	Frustrum near plane
 * @param	far		Frustrum far plane
 * @return	The perspective projection matrix
 */
t_mat4	frustrum(float *hor, float *ver, float near, float far)
{
	return ((t_mat4){{
			{{2.0f * near / (hor[1] - hor[0]), 0.0f,
					(hor[1] + hor[0]) / (hor[1] - hor[0]), 0.0f}},
			{{0.0f, 2.0f * near / (ver[1] - ver[0]),
					(ver[1] + ver[0]) / (ver[1] - ver[0]), 0.0f}},
			{{0.0f, 0.0f, -(far + near) / (far - near),
					-(2.0f * far * near) / (far - near)}},
			{{0.0f, 0.0f, -1.0f, 0.0f}}}});
}
