/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_events_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:59:57 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/06 07:59:57 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "callbacks.h"
#include "MLX42/MLX42_Int.h"

/**
 * Helper function to set OpenGL float uniform value.
 *
 * @param	pg	Specifies the program object to be queried
 * @param	id	The name of the uniform variable whose location is to be queried
 * @param	a	The value to be assigned to the uniform
 */
static void	set_float(uint32_t pg, char *id, float a)
{
	glUniform1f(glGetUniformLocation(pg, id), a);
}

/**
 * Helper function to set OpenGL vec2 uniform entries.
 *
 * @param	pg	Specifies the program object to be queried
 * @param	id	The name of the uniform variable whose location is to be queried
 * @param	a	The value to be assigned to the first entry of the uniform
 * @param	b	The value to be assigned to the second entry of the uniform
 */
static void	set_float2(uint32_t pg, char *id, float a, float b)
{
	glUniform2f(glGetUniformLocation(pg, id), a, b);
}

/**
 * Helper function to set OpenGL mat4 uniform entries.
 *
 * @param	pg	Specifies the program object to be queried
 * @param	id	The name of the uniform variable whose location is to be queried
 * @param	m	The matrix values to be assigned to the uniform entries
 */
static void	set_mat4(uint32_t pg, char *id, t_mat4 m)
{
	glUniformMatrix4fv(glGetUniformLocation(pg, id), 1, GL_FALSE, (float *)m.e);
}

/**
 * Callback function used to render each frame, calling the corresponding shader
 * program and setting up all uniforms needed to render the frame.
 *
 * @param	fdf		Pointer to fdf struct
 */
void	loop_hook(void *param)
{
	int			n;
	t_fdf		*fdf;
	uint32_t	program;

	fdf = (t_fdf *)param;
	program = fdf->program[fdf->selection[0]];
	if (fdf->animate)
		fdf->view[0] = rotate(fdf->view[0], 0.001, (t_vec4){{0, 0, 1, 0}});
	if (fdf->selection[0] == 1)
		set_float(program, "param", fdf->params.e[0]);
	else if (fdf->selection[0] > 1)
	{
		set_float(program, "radius", fdf->params.e[1]);
		set_float2(program, "length",
			fdf->params.e[2], fdf->params.e[3]);
	}
	glUseProgram(program);
	set_mat4(program, "model", transpose(fdf->model[0]));
	set_mat4(program, "view", transpose(fdf->view[0]));
	set_mat4(program, "proj", transpose(fdf->proj[fdf->selection[1]]));
	n = 2 * (2 * fdf->map.dim[0] * fdf->map.dim[1]
			- fdf->map.dim[0] - fdf->map.dim[1]);
	glDrawElements(GL_LINES, n, GL_UNSIGNED_INT, 0);
}
