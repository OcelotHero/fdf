/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:40:10 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:54:13 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>

# include "types.h"

t_mat4	zeros(void);
t_mat4	eye(void);
t_mat4	diag(t_vec4 vec);

t_mat4	mat_mat(t_mat4 A, t_mat4 B);
t_vec4	mat_vec(t_mat4 A, t_vec4 b);
t_mat4	transpose(t_mat4 mat);

t_mat4	scale(t_mat4 mat, t_vec4 vec);
t_mat4	translate(t_mat4 mat, t_vec4 vec);
t_mat4	rotate(t_mat4 mat, float rad, t_vec4 vec);

t_mat4	ortho(float width, float height, float near, float far);
t_mat4	perspective(float fovy, float aspect, float near, float far);

#endif
