/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:21:13 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 06:26:45 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>

# include "libft.h"
# include "errors.h"
# include "types.h"
# include "ft_printf.h"
# include "MLX42/MLX42.h"

# define BASE "0123456789abcdef"

bool	is_space(char c);
bool	is_valid(char c);
t_vec4	int_to_col(int color);
void	set_img_px_col(mlx_image_t *img, t_vec4 pos, t_vec4 col);

int		cleanup(t_fdf *fdf, int error);

int		n_atoi_base(const char *str, char *base, int radix, int *val);

#endif
