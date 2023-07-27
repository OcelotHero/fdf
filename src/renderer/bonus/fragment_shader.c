/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment_shader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:55:46 by rraharja          #+#    #+#             */
/*   Updated: 2023/04/08 05:55:46 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opengl.h"

/**
 * Returns a basic fragment shader.
 *
 * @return	Fragment shader source code
 */
const char	*get_fshader_basic(void)
{
	const char	*source = "#version 330 core\n"
		"in vec4 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = ourColor;\n"
		"}\0";

	return (source);
}
