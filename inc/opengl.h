/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 02:55:46 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/31 02:55:46 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_H
# define OPENGL_H

# include <math.h>

# include "libft.h"
# include "maths.h"
# include "types.h"
# include "ft_printf.h"
# include "MLX42/MLX42_Int.h"

# ifdef __APPLE__
#  define DENSITY 2
# else
#  define DENSITY 1
# endif

int			setup_buffer_objects(t_map *map);

const char	*get_fshader_basic(void);

const char	*get_vshader_basic(void);
const char	*get_vshader_globe(void);
const char	*get_vshader_warping(void);
const char	*get_vshader_parabolic(void);
const char	*get_vshader_vanishing(void);

uint32_t	create_shader_program(const char *vsource, const char *fsource);

#endif
