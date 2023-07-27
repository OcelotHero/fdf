/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:01:04 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/06 08:01:04 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "callbacks.h"

/**
 * Callback function used to handle window resizing to maintain correct aspect
 * ratio.
 *
 * @param	width	The new width of the window
 * @param	height	The new height of the window
 * @param	param	Pointer to fdf struct
 */
void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->proj[0] = ortho(2.0f * width / (float)HEIGHT,
			2.0f * height / (float)HEIGHT, 0.1f, 100.0f);
	fdf->proj[1] = perspective(2 * atan(height / (float)HEIGHT
				* tan(M_PI_4 / 2.0f)), width / (float)height, 0.1f, 100.0f);
}
