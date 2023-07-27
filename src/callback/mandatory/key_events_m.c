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
 * Callback function used to handle key presses:
 * 		Esc	To quit application
 * 		R	To reset to default view
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
		draw_map(fdf->img, &fdf->map, fdf->map.base, true);
}
