/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 09:55:01 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/06 15:04:57 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define WIDTH 1280
# define HEIGHT 720

# include <stdbool.h>

# include "MLX42/MLX42.h"

/* A union to store a 4 column vector in multiple format */
typedef union s_vec4 {
	struct {
		float	x;
		float	y;
		float	z;
		float	w;
	};
	struct {
		float	r;
		float	g;
		float	b;
		float	a;
	};
	float	e[4];
}	t_vec4;

/* A structure to represent a point */
typedef struct s_point {
	bool	drawn;
	t_vec4	col;
	t_vec4	pos;
}	t_point;

typedef struct s_mat4 {
	t_vec4	e[4];
}	t_mat4;

typedef struct s_map {
	int		dim[2];
	t_vec4	lim[2];
	t_vec4	origin;
	t_mat4	tf;
	t_mat4	base;
	t_point	*data;
}	t_map;

typedef struct s_fdf {
	int			pos[2];
	int			source[2];
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_mat4		model[2];
	t_mat4		view[2];
	t_mat4		proj[2];
	bool		animate;
	int			selection[2];
	uint32_t	program[5];
	t_vec4		params;
}	t_fdf;

#endif
