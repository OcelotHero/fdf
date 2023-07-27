/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:18:08 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:18:08 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

/**
 * Returns an array containing a pointer to the four ordinal neighbour of the
 * given point from the given map.
 *
 * @param	map	Pointer to map struct
 * @param	i	Index of the point on the map whose neighbour is to be queried
 * @return	Pointers to the neighbours of the given point
 */
static t_point	**get_neighbours(t_map *map, int i)
{
	int				idx;
	static t_point	*neighbours[4];

	idx = i;
	idx -= map->dim[0] * (i - map->dim[0] >= 0);
	neighbours[0] = &map->data[idx];
	idx = i;
	idx += ((i + 1) / map->dim[0] == i / map->dim[0]);
	neighbours[1] = &map->data[idx];
	idx = i;
	idx += map->dim[0] * (i + map->dim[0] < map->dim[0] * map->dim[1]);
	neighbours[2] = &map->data[idx];
	idx = i;
	idx -= (i != 0 && (i - 1) / map->dim[0] == i / map->dim[0]);
	neighbours[3] = &map->data[idx];
	return (neighbours);
}

/**
 * Updates the map metadata after applying the linear transformation matrix
 *
 * @param	map		Pointer to map struct
 * @param	mat		The transformation matrix applied to the map
 * @param	reset	Whether to reset the metadata to the default
 */
static void	update_map_metadata(t_map *map, t_mat4 mat, bool reset)
{
	if (reset)
		map->origin = (t_vec4){{(map->dim[0] - 1) / 2.0f,
			(map->dim[1] - 1) / 2.0f, 0, 1}};
	map->origin = mat_vec(mat, map->origin);
}

/**
 * Applies the transformation matrix to the given point
 *
 * @param	point	Pointer to map struct
 * @param	mat		The transformation matrix to apply
 * @return	The transformed point
 */
static t_point	transform_point(t_point point, t_mat4 mat)
{
	t_point	res;

	res = point;
	res.pos = mat_vec(mat, point.pos);
	return (res);
}

/**
 * Draws the map to image object after applying the transformation matrix
 *
 * @param	img		Pointer to image on which to draw
 * @param	map		Pointer to map struct to be drawn
 * @param	mat		The transformation matrix to apply to the map
 * @param	reset	Whether to apply the transformation matrix to the original
 * 					or the transformed map
 */
void	draw_map(mlx_image_t *img, t_map *map, t_mat4 mat, bool reset)
{
	int		i;
	int		j;
	t_point	**neighbours;

	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
	if (reset)
		map->tf = eye();
	map->tf = mat_mat(mat, map->tf);
	i = -1;
	while (++i < (map->dim[0] * map->dim[1]))
	{
		j = -1;
		neighbours = get_neighbours(map, i);
		while (++j < 4)
			if (neighbours[j]->drawn && (&map->data[i] != neighbours[j]))
				draw_wu_line(img, transform_point(map->data[i], map->tf),
					transform_point(*neighbours[j], map->tf));
		map->data[i].drawn = true;
	}
	update_map_metadata(map, mat, reset);
	i = -1;
	while (++i < (map->dim[0] * map->dim[1]))
		map->data[i].drawn = false;
}
