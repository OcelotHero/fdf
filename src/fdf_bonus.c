/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:16:35 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/15 20:38:51 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include "utils.h"
#include "types.h"
#include "opengl.h"
#include "parser.h"
#include "renderer.h"
#include "callbacks.h"

#include <time.h>
#include <memory.h>
#include "MLX42/MLX42_Int.h"

/**
 * Calculates the scaling ratio needed so that the isomestric map projection
 * fits into the window.
 *
 * @param	map	Pointer to map struct
 * @return	The scaling ratio
 */
static float	auto_scaling_ratio(t_map *map)
{
	float	h_range;
	float	v_range;
	t_mat4	mat;

	mat = rotate(eye(), atan(sqrt(2)), (t_vec4){{1, 0, 0, 0}});
	mat = rotate(mat, M_PI_4, (t_vec4){{0, 0, 1, 0}});
	mat = translate(mat, (t_vec4){{-map->origin.x, -map->origin.y, 0, 1}});
	h_range = (mat_vec(mat, (t_vec4){{map->lim[1].x, 0, 0, 1}}).x
			- mat_vec(mat, (t_vec4){{0, map->lim[1].y, 0, 1}}).x);
	v_range = (mat_vec(mat, (t_vec4){{map->lim[1].x, map->lim[1].y, 0, 1}}).y
			- mat_vec(mat, (t_vec4){{0, 0, 0, 1}}).y);
	return (fminf(WIDTH / h_range, HEIGHT / v_range));
}

/**
 * Initializes the default view for all view modes.
 *
 * @param	fdf	Pointer to fdf struct
 */
static void	initialize_default(t_fdf *fdf)
{
	float	range;
	float	ratio;
	float	aspect;
	t_mat4	mat;

	ratio = auto_scaling_ratio(&fdf->map);
	range = fdf->map.lim[1].z - fdf->map.lim[0].z;
	range = !range + range;
	mat = scale(eye(), (t_vec4){{2.0f / (float)HEIGHT,
			-2.0f / (float)HEIGHT, 2.0f / (float)HEIGHT, 1.0f}});
	mat = scale(mat, (t_vec4){{ratio * 0.9f, ratio * 0.9f,
			ratio * 0.9f / range, 0}});
	mat = translate(mat, (t_vec4){{-fdf->map.origin.x,
			-fdf->map.origin.y, 0, 1}});
	ft_memcpy(fdf->model, (t_mat4 []){mat, mat}, 2 * sizeof(*fdf->model));
	mat = translate(eye(), (t_vec4){{.0f, .0f, -3.0f, .0f}});
	mat = rotate(mat, -atan(sqrt(2)), (t_vec4){{1, 0, 0, 0}});
	mat = rotate(mat, -M_PI_4, (t_vec4){{0, 0, 1, 0}});
	ft_memcpy(fdf->view, (t_mat4 []){mat, mat}, 2 * sizeof(*fdf->view));
	aspect = WIDTH / (float)HEIGHT;
	fdf->proj[0] = ortho(2.0f * aspect, 2.0f, 0.1f, 100.0f);
	fdf->proj[1] = perspective(2 * M_PI_4 / 2.0f, aspect, 0.1f, 100.0f);
	ft_memcpy(fdf->selection, (int []){0, 0}, 2 * sizeof(*fdf->selection));
	fdf->animate = false;
	fdf->params = (t_vec4){{0, 1000.f, 1.f, 1.f}};
}

/**
 * Creates shader programs for different view modes.
 *
 * @param	fdf	Pointer to fdf struct
 * @return	Whether the operation was successful
 */
static int	setup_shader_program(t_fdf *fdf)
{
	int	i;

	fdf->program[0] = create_shader_program(get_vshader_basic(),
			get_fshader_basic());
	fdf->program[1] = create_shader_program(get_vshader_parabolic(),
			get_fshader_basic());
	fdf->program[2] = create_shader_program(get_vshader_globe(),
			get_fshader_basic());
	fdf->program[3] = create_shader_program(get_vshader_vanishing(),
			get_fshader_basic());
	fdf->program[4] = create_shader_program(get_vshader_warping(),
			get_fshader_basic());
	i = -1;
	while (++i < 5)
		if (!fdf->program[i])
			return (1);
	return (0);
}

/**
 * Draws an isometric wireframe view of a terrain map from the given .fdf file
 * to a window.
 */
int	main(int narg, char **args)
{
	int		error;
	t_fdf	fdf;

	if (narg != 2)
		return (cleanup(NULL, 1));
	fdf = (t_fdf){.mlx = NULL, .map.data = NULL};
	error = parse_file(args[1], &fdf);
	if (error)
		return (error);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf.mlx)
		return (cleanup(&fdf, 9));
	error = setup_buffer_objects(&fdf.map) + 2 * setup_shader_program(&fdf);
	if (error)
		return (cleanup(&fdf, 5 + error - (error == 3)));
	initialize_default(&fdf);
	mlx_key_hook(fdf.mlx, key_hook, &fdf);
	mlx_mouse_hook(fdf.mlx, mouse_hook, &fdf);
	mlx_cursor_hook(fdf.mlx, cursor_hook, &fdf);
	mlx_scroll_hook(fdf.mlx, scroll_hook, &fdf);
	mlx_resize_hook(fdf.mlx, resize_hook, &fdf);
	if (!mlx_loop_hook(fdf.mlx, loop_hook, &fdf))
		return (cleanup(&fdf, 8));
	mlx_loop(fdf.mlx);
	return (cleanup(&fdf, 0));
}
