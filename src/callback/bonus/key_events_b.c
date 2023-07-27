/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 05:47:32 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 05:47:32 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "callbacks.h"

/**
 * A helper function to handle key presses:
 * 		WASD/Arrow keys	To increment or decrement parameters used in mode 3 - 5
 *
 * @param	keydata	The callback data, containing info on key
 * @param	fdf		Pointer to fdf struct
 */
static void	modify_param(mlx_key_data_t keydata, t_fdf *fdf)
{
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->params.e[3] -= 0.01f;
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->params.e[3] += 0.01f;
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->params.e[2] -= 0.01f;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		fdf->params.e[2] += 0.01f;
}

/**
 * Callback function used to handle key presses:
 * 		Esc		To quit application
 * 		R		To reset to default view
 * 		P		To change between isometric and perspective projection
 * 		1 - 5	To toggle between different warping modes
 * 		Space	To toggle rotation along the map z-axis
 *
 * @param	keydata	The callback data, containing info on key
 * @param	param	Pointer to fdf struct
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(cleanup(fdf, 0));
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->model[0] = fdf->model[1];
		fdf->view[0] = fdf->view[1];
		fdf->params = (t_vec4){{0, 10.f, 1.f, 1.f}};
	}
	else if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_5
		&& keydata.action == MLX_PRESS)
		fdf->selection[0] = keydata.key - MLX_KEY_1;
	else if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		fdf->selection[1] = !fdf->selection[1];
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		fdf->animate = !fdf->animate;
	else if (fdf->selection[0] > 1)
		modify_param(keydata, fdf);
}
