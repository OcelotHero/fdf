/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:17:57 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 21:17:57 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opengl.h"

/**
 * Generates an array of vertices containing the position and color of each
 * point from the given map.
 *
 * @param	map	Pointer to map struct
 * @return	Array of vertices containing position and color of each vertex
 */
static float	*generate_vertices(t_map *map)
{
	int		n;
	float	*vtx;

	vtx = malloc(sizeof(*vtx) * 8 * map->dim[0] * map->dim[1]);
	if (!vtx)
		return (NULL);
	n = -1;
	while (++n < map->dim[0] * map->dim[1])
	{
		ft_memcpy(&vtx[8 * n], &map->data[n].pos.e[0], sizeof(*vtx) * 4);
		ft_memcpy(&vtx[8 * n + 4], &map->data[n].col.e[0], sizeof(*vtx) * 4);
	}
	return (vtx);
}

/**
 * Generates an array of indices indicating which point should form a line to
 * create the terrain map.
 *
 * @param	map	Pointer to map struct
 * @return	Array of indices that forms a line
 */
static uint32_t	*generate_indices(t_map *map)
{
	int			i;
	int			j;
	int			n;
	uint32_t	*idx;

	idx = malloc(sizeof(*idx) * 2
			* (2 * map->dim[0] * map->dim[1] - map->dim[0] - map->dim[1]));
	if (!idx)
		return (NULL);
	n = 0;
	j = -1;
	while (++j < map->dim[1])
	{
		i = -1;
		while (++i < map->dim[0])
		{
			idx[n] = i + map->dim[0] * j;
			idx[n + 1] = i + map->dim[0] * j + 1;
			n += 2 * (i != (map->dim[0] - 1));
			idx[n] = i + map->dim[0] * j;
			idx[n + 1] = i + map->dim[0] * (j + 1);
			n += 2 * (j != (map->dim[1] - 1));
		}
	}
	return (idx);
}

/**
 * Move map points to buffer to be rendered by the shader programs.
 *
 * @param	map	Pointer to map struct
 * @return	Whether the operation was successful
 */
static int	move_map_to_buffer(t_map *map)
{
	int				n;
	float			*vx;
	uint32_t		*ix;
	unsigned int	vbo;
	unsigned int	ebo;

	vx = generate_vertices(map);
	n = 8 * map->dim[0] * map->dim[1];
	if (!vx)
		return (1);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(*vx), vx, GL_STATIC_DRAW);
	free(vx);
	ix = generate_indices(map);
	n = n / 2 - 2 * (map->dim[0] + map->dim[1]);
	if (!ix)
		return (1);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, n * sizeof(*ix), ix, GL_STATIC_DRAW);
	free(ix);
	return (0);
}

/**
 * Setup buffer objects to store the map points.
 *
 * @param	map	Pointer to map struct
 * @return	Whether the operation was successful
 */
int	setup_buffer_objects(t_map *map)
{
	int				error;
	unsigned int	vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	error = move_map_to_buffer(map);
	if (error)
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return (1);
	}
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(vao);
	return (0);
}
