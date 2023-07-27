/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:16:35 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/15 20:29:23 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include "utils.h"
#include "types.h"
#include "parser.h"
#include "renderer.h"
#include "callbacks.h"
#include "MLX42/MLX42.h"

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
 * Draws the map in isometric projection and saves the transformtion matrix as
 * the default view.
 *
 * @param	fdf	Pointer to fdf struct
 */
static void	draw_isometric(t_fdf *fdf)
{
	float	range;
	float	ratio;
	t_mat4	mat;

	ratio = auto_scaling_ratio(&fdf->map);
	range = fdf->map.lim[1].z - fdf->map.lim[0].z;
	range = !range + range;
	mat = translate(eye(), (t_vec4){{WIDTH / 2.0f, HEIGHT / 2.0f, 0, 0}});
	mat = rotate(mat, atan(sqrt(2)), (t_vec4){{1, 0, 0, 0}});
	mat = rotate(mat, M_PI_4, (t_vec4){{0, 0, 1, 0}});
	mat = scale(mat,
			(t_vec4){{ratio * 0.9f, ratio * 0.9f, ratio * .9f / range, 0}});
	mat = translate(mat,
			(t_vec4){{-fdf->map.origin.x, -fdf->map.origin.y, 0, 1}});
	fdf->map.base = mat;
	draw_map(fdf->img, &fdf->map, mat, true);
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
	if (!ft_strnstr(args[1], ".fdf", ft_strlen(args[1])))
		return (cleanup(NULL, 2));
	fdf = (t_fdf){.mlx = NULL, .map.data = NULL};
	error = parse_file(args[1], &fdf);
	if (error)
		return (error);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf.mlx)
		return (cleanup(&fdf, 9));
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.img)
		return (cleanup(&fdf, 9));
	draw_isometric(&fdf);
	mlx_key_hook(fdf.mlx, key_hook, &fdf);
	mlx_mouse_hook(fdf.mlx, mouse_hook, &fdf);
	mlx_cursor_hook(fdf.mlx, cursor_hook, &fdf);
	mlx_scroll_hook(fdf.mlx, scroll_hook, &fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
	return (cleanup(&fdf, 0));
}
