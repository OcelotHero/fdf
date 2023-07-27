/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:01:33 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/07 01:51:04 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Reads from the file given in the file descriptor the size of the map to
 * generate and stores it to the map struct.
 *
 * @param	fd	File descriptor of the .fdf file
 * @param	map	Map struct to store size metadata
 * @return	Whether the file is correctly formated and thus be parsed
 */
static int	get_map_size(int fd, t_map *map)
{
	int		*n;
	char	buf[BUFSIZ];

	ft_memcpy(map->dim, (int [2]){0, 0}, 2 * sizeof(*map->dim));
	n = (int []){read(fd, buf, BUFSIZ), 0, 0, 1, '\n'};
	while (n[0] > 0)
	{
		n[1] = -1;
		while (++n[1] < n[0])
		{
			n[3] += (!n[3] && is_space(buf[n[1]]));
			n[2] += (n[3] && is_valid(buf[n[1]]));
			n[3] -= (n[3] && is_valid(buf[n[1]]));
			if (buf[n[1]] == '\n' && map->dim[1] && map->dim[0] != n[2])
				return (2);
			map->dim[0] += n[2] * (buf[n[1]] == '\n' && !map->dim[1]);
			map->dim[1] += (buf[n[1]] == '\n' && n[2]);
			n[2] -= n[2] * (buf[n[1]] == '\n');
		}
		n[4] = buf[n[1] - 1];
		n[0] = read(fd, buf, BUFSIZ);
	}
	map->dim[0] += n[2] * !map->dim[1];
	map->dim[1] += n[4] != '\n';
	return (n[0] != 0 + !n[0] * 2 *(map->dim[0] != n[2] && n[4] != '\n'));
}

/**
 * Initializes the attributes of a new point at the given index from the map to
 * a given base value - z-height or modify them to the given value - color
 *
 * @param	new	Whether to initialize a base attribute to the point or modify it
 * @param	map	Map struct where the points are stored
 * @param	idx	The index of the point to modify from the list of points
 * @param	val	Value to set
 */
static void	set_point_attribute(bool new, t_map *map, int idx, int val)
{
	if (idx >= map->dim[0] * map->dim[1])
		return ;
	if (new)
	{
		map->data[idx] = (t_point){
			.pos = {{idx % map->dim[0], idx / map->dim[0], val, 1.0f}},
			.col = {{1.0f, 1.0f, 1.0f, 1.0f}},
			.drawn = false};
		if (map->lim[0].z > val)
			map->lim[0].z = val;
		if (map->lim[1].z < val)
			map->lim[1].z = val;
	}
	else
		map->data[idx].col = int_to_col(val);
}

/**
 * Populates the map struct with points, each containing data parsed from the
 * file given in the file descriptor.
 *
 * @param	fd	File descriptor of the .fdf file
 * @param	map	Map struct where the points are stored
 * @return	Whether the file is correctly formated and thus be parsed
 */
static int	populate_map(int fd, t_map *map)
{
	int		*n;
	char	buf[BUFSIZ + 1];

	n = (int []){0, 0, -1, 0, 0, read(fd, buf, BUFSIZ)};
	while (n[5] > 0)
	{
		n[2] -= (!n[0] && n[2] != -1);
		n[0] -= (n[0] && is_space(buf[0]));
		n[4] -= n[4] * !n[0];
		n[1] -= n[1] * !n[0];
		buf[n[5]] = '\0';
		while (n[3] < n[5] && (n[2] < map->dim[0] * map->dim[1]))
		{
			n[3] += n_atoi_base(&buf[n[3]], BASE, 10 + 6 * n[1], &n[4]);
			n[2] += 1 - (n[0] || n[1]);
			n[0] -= n[0];
			set_point_attribute(!n[1], map, n[2], n[4]);
			n[4] -= n[4] * (is_space(buf[n[3]]) || buf[n[3]] == ',');
			n[1] = (buf[n[3]] == ',' || (n[1] && !buf[n[3]]));
			n[3] += 3 * (buf[n[3]] == ',');
		}
		ft_memcpy(n, (int [6]){!is_space(buf[n[5] - 1]), n[1], n[2],
			n[3] - n[5], n[4], read(fd, buf, BUFSIZ)}, 6 * sizeof(*n));
	}
	return (n[5] == -1);
}

/**
 * Initializes the map struct and allocates the neccessary memory to store a
 * list of points.
 *
 * @param	map	Map struct to initialize
 * @return	Whether memory can be allocated to store data
 */
static int	init_map(t_map *map)
{
	map->tf = eye();
	map->data = malloc(sizeof(*(map->data)) * map->dim[0] * map->dim[1]);
	if (!map->data)
		return (1);
	map->lim[0] = (t_vec4){{0, 0, INT_MAX, 1}};
	map->lim[1] = (t_vec4){{map->dim[0] - 1, map->dim[1] - 1, INT_MIN, 1}};
	map->origin = (t_vec4){{map->lim[1].x / 2.0f, map->lim[1].y / 2.0f, 0, 1}};
	return (0);
}

/**
 * Reads the file given as filename, parsing, and storing the data contained to
 * fdf struct given. If any error occurs, a specific error code is returned.
 *
 * @param	filename	Filename of the .fdf file
 * @param	fdf			fdf struct where the map is stored.
 * @return	Whether the file can be correctly accessed, read, and parsed and
 * 			memory allocated properly
 */
int	parse_file(const char *filename, t_fdf *fdf)
{
	int	fd;
	int	error;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (cleanup(fdf, 2));
	error = get_map_size(fd, &fdf->map);
	error = 3 * !error * (!fdf->map.dim[0] || !fdf->map.dim[1]);
	close(fd);
	if (error)
		return (cleanup(fdf, error + 2));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (cleanup(fdf, 2));
	error = 2 * init_map(&fdf->map);
	if (!error)
		error = populate_map(fd, &fdf->map);
	close(fd);
	if (error)
		return (cleanup(fdf, 3 * error));
	return (0);
}
