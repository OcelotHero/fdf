/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:51:18 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/15 20:50:09 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "callbacks.h"
#include "MLX42/MLX42_Int.h"

/**
 * Rotates the map view along the display x and y-axis.
 *
 * @param	fdf		Pointer to fdf struct
 * @param	delta	The x and y delta of mouse movement
 */
static void	rotate_map(t_fdf *fdf, double *delta)
{
	t_mat4	mat;

	mat = translate(eye(), (t_vec4){{fdf->view[0].e[0].e[3],
			fdf->view[0].e[1].e[3], fdf->view[0].e[2].e[3], 0}});
	mat = rotate(mat, .01f * ((delta[0] > 0) - (delta[0] < 0)),
			(t_vec4){{0, 1, 0, 0}});
	mat = rotate(mat, .01f * ((delta[1] > 0) - (delta[1] < 0)),
			(t_vec4){{1, 0, 0, 0}});
	mat = translate(mat, (t_vec4){{-fdf->view[0].e[0].e[3],
			-fdf->view[0].e[1].e[3], -fdf->view[0].e[2].e[3], 0}});
	fdf->view[0] = mat_mat(mat, fdf->view[0]);
}

/**
 * Scales the z elevation of the map.
 *
 * @param	fdf		Pointer to fdf struct
 * @param	delta	The x and y delta of mouse movement
 */
static void	scale_map_elevation(t_fdf *fdf, double *delta)
{
	bool	swap;
	double	mul;
	double	scalar;

	swap = fabs(fdf->model[0].e[2].e[2] * fdf->map.lim[1].z) < 0.0002;
	mul = fdf->model[0].e[2].e[2];
	mul = (mul > 0) - (mul < 0);
	scalar = 1 - (!swap - swap) * mul * 0.01 * delta[1];
	scalar *= !swap - swap;
	fdf->model[0] = scale(fdf->model[0], (t_vec4){{1, 1, scalar, 1}});
}

/**
 * Callback function used to handle scrolling, scaling (zooming) the map view
 * either up or down depending on the scroll direction. Increment or decrement
 * a parameter while in mode 2 - 5 if the CTRL buutton is pressed.
 *
 * @param	xdelta	The mouse x delta
 * @param	ydelta	The mouse y delta
 * @param	param	Pointer to fdf struct
 */
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	double	scalar;
	t_mat4	mat;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (fdf->selection[0] > 0
		&& (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT_CONTROL)
			|| mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_CONTROL)))
	{
		scalar = 50.0f;
		if (fdf->selection[0] != 1)
			scalar /= -fmax(fabs(fdf->params.e[1]), 0.1f);
		fdf->params.e[fdf->selection[0] != 1] -= ydelta / scalar;
	}
	else
	{
		scalar = 1.0f + ydelta / 50.0f;
		mat = scale(eye(), (t_vec4){{scalar, scalar, scalar, 1}});
		fdf->view[0] = mat_mat(fdf->view[0], mat);
	}
	(void)xdelta;
}

/**
 * Callback function used to handle raw mouse movement, either translating,
 * rotating or changing the elevation of the map depending on the button pressed
 * and whether the CTRL button is pressed.
 *
 * @param	xpos	The mouse x position
 * @param	ypos	The mouse y position
 * @param	param	Pointer to fdf struct
 */
void	cursor_hook(double xpos, double ypos, void *param)
{
	double	*delta;
	t_fdf	*fdf;
	t_mat4	mat;

	fdf = (t_fdf *)param;
	delta = (double []){xpos - fdf->pos[0], ypos - fdf->pos[1]};
	if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mat = translate(eye(), (t_vec4){{2.f / HEIGHT * delta[0],
				-2.f / HEIGHT * delta[1], 0, 0}});
		fdf->view[0] = mat_mat(mat, fdf->view[0]);
	}
	else if (mlx_is_mouse_down(fdf->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT_CONTROL)
			|| mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_CONTROL))
			scale_map_elevation(fdf, delta);
		else
			rotate_map(fdf, delta);
	}
	ft_memcpy(fdf->pos, (int [2]){xpos, ypos}, 2 * sizeof(int));
}

/**
 * Callback function used to handle mouse actions, storing where the mouse is
 * clicked.
 *
 * @param	button	The mouse button/key pressed
 * @param	action	The mouse action that took place
 * @param	mods	The modifier keys pressed together with the mouse key
 * @param	param	Pointer to fdf struct
 */
void	mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (action == MLX_PRESS)
		mlx_get_mouse_pos(fdf->mlx, &fdf->pos[0], &fdf->pos[1]);
	(void)button;
	(void)mods;
}
