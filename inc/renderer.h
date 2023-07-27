/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:46:51 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 06:50:56 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include <math.h>
# include <stdbool.h>

# include "maths.h"
# include "types.h"
# include "libft.h"
# include "MLX42/MLX42.h"

# define LIN_BRIGHT 1

void	draw_point(mlx_image_t *img, t_vec4 pos, t_vec4 col, bool steep);

void	draw_wu_line(mlx_image_t *img, t_point a, t_point b);
void	draw_bresenham_line(mlx_image_t *img, t_point a, t_point b);

void	draw_map(mlx_image_t *img, t_map *map, t_mat4 mat, bool reset);

#endif
