/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:16:23 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 06:43:52 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

/**
 * Interpolates between the color a and color b with the given parameter t and
 * brightness.
 *
 * @param	t			Parameterized coordinate [0, 1], i.e. interpolator
 * @param	a			The starting color
 * @param	b			The final color
 * @param	brightness	The brightness value to affect the output color
 * @return	The resulting interpolated color multiplies by brightness value
 */
static t_vec4	lerp_col(float t, t_vec4 a, t_vec4 b, float brightness)
{
	t_vec4	col;

	col.r = b.r * t + a.r * (1.0f - t);
	col.g = b.g * t + a.g * (1.0f - t);
	col.b = b.b * t + a.b * (1.0f - t);
	if (LIN_BRIGHT)
		col.a = b.a * t + a.a * (1.0f - t);
	else
		col.a = b.a * exp(-3.0f * (1.0f - t)) + a.a * exp(-3.0f * t);
	col.a *= brightness;
	return (col);
}

/**
 * Auxiliary function to perform necessary endpoints swapping necessary for
 * the Bresenham and Xiaolin Wu line algorithm
 *
 * @param	steep	Indicates whether the (x,y) pixel location of the given
 * 					points are to be swapped
 * @param	a		The starting point
 * @param	b		The final point
 */
static void	adjust_line_endpoint(bool steep, t_point *a, t_point *b)
{
	t_point	tmp;

	if (steep)
	{
		tmp = *a;
		a->pos.x = a->pos.y;
		a->pos.y = tmp.pos.x;
		tmp = *b;
		b->pos.x = b->pos.y;
		b->pos.y = tmp.pos.x;
	}
	if (a->pos.x > b->pos.x)
	{
		tmp = *a;
		a->pos = b->pos;
		a->col = b->col;
		b->pos = tmp.pos;
		b->col = tmp.col;
	}
}

/**
 * Draws a line from point a to point b, with the given configurations, i.e.
 * position and color, using Xiaolin Wu line drawing algorithm to the given
 * image.
 *
 * @param	img	Pointer to the image
 * @param	a	The starting point
 * @param	b	The final point
 */
void	draw_wu_line(mlx_image_t *img, t_point a, t_point b)
{
	bool	steep;
	float	dx;
	float	dy;
	float	gradient;
	float	y;

	steep = (fabs(b.pos.y - a.pos.y) > fabs(b.pos.x - a.pos.x));
	adjust_line_endpoint(steep, &a, &b);
	draw_point(img, a.pos, a.col, steep);
	draw_point(img, b.pos, b.col, steep);
	dx = b.pos.x - a.pos.x;
	dy = b.pos.y - a.pos.y;
	gradient = dy / dx;
	y = a.pos.y + gradient;
	while (a.pos.x++ < b.pos.x - 1)
	{
		draw_point(img, (t_vec4){{a.pos.x, y, 0.0, 1.0}},
			lerp_col(1 - (b.pos.x - a.pos.x) / dx,
				a.col, b.col, (1.0f - (y - (int) y))), steep);
		draw_point(img, (t_vec4){{a.pos.x, y + 1.0, 0.0, 1.0}},
			lerp_col(1 - (b.pos.x - a.pos.x) / dx,
				a.col, b.col, y - (int) y), steep);
		y += gradient;
	}
}

/**
 * Draws a line from point a to point b, with the given configurations, i.e.
 * position and color, using Bresenham line drawing algorithm to the given
 * image.
 *
 * @param	img	Pointer to the image
 * @param	a	The starting point
 * @param	b	The final point
 */
void	draw_bresenham_line(mlx_image_t *img, t_point a, t_point b)
{
	bool	steep;
	int		dx;
	int		dy;
	int		error;
	int		ystep;

	steep = (fabsf(b.pos.y - a.pos.y) > fabsf(b.pos.x - a.pos.x));
	adjust_line_endpoint(steep, &a, &b);
	dx = b.pos.x - a.pos.x;
	dy = fabsf(b.pos.y - a.pos.y);
	error = dx / 2;
	ystep = (a.pos.y < b.pos.y) - !(a.pos.y < b.pos.y);
	while (a.pos.x <= b.pos.x)
	{
		draw_point(img, a.pos,
			lerp_col(1 - (b.pos.x - a.pos.x) / (float) dx,
				a.col, b.col, 1), steep);
		error -= dy;
		if (error < 0)
		{
			a.pos.y += ystep;
			error += dx;
		}
		a.pos.x++;
	}
}
