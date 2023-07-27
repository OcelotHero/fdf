/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:20:30 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:20:30 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

/**
 * Sets the color of a pixel of the given image.
 *
 * @param	img	Pointer to the image
 * @param	pos	The (x,y) pixel location in display coordinate, given as vec4
 * 				format
 * @param	col The color for the pixel given in vec4 RGBA format
 */
static void	set_img_px_col(mlx_image_t *img, t_vec4 pos, t_vec4 col)
{
	uint8_t	*px;

	if (pos.x < 0 || pos.x > img->width || pos.y < 0 || pos.y > img->height)
		return ;
	px = img->pixels
		+ ((int) pos.x + (int) pos.y * img->width) * sizeof(int32_t);
	*px = col.r * col.a * 255.0f + *px * (1.0f - col.a);
	px++;
	*px = col.g * col.a * 255.0f + *px * (1.0f - col.a);
	px++;
	*px = col.b * col.a * 255.0f + *px * (1.0f - col.a);
	px++;
	*px = col.a * 255.0f;
}

/**
 * Draws a point at the given location with the given color on the given image.
 *
 * @param	img		Pointer to the image
 * @param	pos		The (x,y) pixel location in display coordinate, given as
 * 					vec4 format
 * @param	col		The color for the pixel given in vec4 RGBA format
 * @param	steep	Indicates whether the (x,y) pixel location is to be swapped
 */
void	draw_point(mlx_image_t *img, t_vec4 pos, t_vec4 col, bool steep)
{
	float	tmp;

	if (steep)
	{
		tmp = pos.y;
		pos.y = pos.x;
		pos.x = tmp;
	}
	set_img_px_col(img, pos, col);
}
