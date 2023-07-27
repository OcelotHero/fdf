/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:27 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 21:16:27 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opengl.h"

/**
 * Returns a basic vertex shader with only linear transformations.
 *
 * @return	Vertex shader source code
 */
const char	*get_vshader_basic(void)
{
	const char	*source = "#version 330 core\n"
		"layout (location = 0) in vec4 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = proj * view * model * aPos;\n"
		"	ourColor = aColor;"
		"}\0";

	return (source);
}

/**
 * Returns a vertex shader with a parabolic transformation.
 *
 * @return	Vertex shader source code
 */
const char	*get_vshader_parabolic(void)
{
	const char	*source = "#version 330 core\n"
		"layout (location = 0) in vec4 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"uniform float param;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	vec4 scaled = model * aPos;\n"
		"	scaled = vec4(scaled.xy, scaled.z - param"
		"		* (pow(scaled.x, 2.) + pow(scaled.y, 2.)), scaled.w);\n"
		"	gl_Position = proj * view * scaled;\n"
		"	ourColor = aColor;"
		"}\0";

	return (source);
}

/**
 * Returns a vertex shader with a spherical coordinate transformation.
 *
 * @return	Vertex shader source code
 */
const char	*get_vshader_globe(void)
{
	const char	*source = "#version 330 core\n"
		"layout (location = 0) in vec4 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"uniform float radius;\n"
		"uniform vec2 length;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	vec4 scaled = model * aPos;\n"
		"	float theta = scaled.x / (length.x * radius);\n"
		"	float phi = scaled.y / (length.y * radius);\n"
		"	scaled = vec4("
		"		(radius + scaled.z) * sin(theta) * cos(phi),"
		"		(radius + scaled.z) * sin(phi),"
		"		(radius + scaled.z) * cos(theta) * cos(phi) - radius,"
		"		scaled.w);\n"
		"	gl_Position = proj * view * scaled;\n"
		"	ourColor = aColor;"
		"}\0";

	return (source);
}

/**
 * Returns a vertex shader with 2 vanishing points transformation.
 *
 * @return	Vertex shader source code
 */
const char	*get_vshader_vanishing(void)
{
	const char	*source = "#version 330 core\n"
		"layout (location = 0) in vec4 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"uniform float radius;\n"
		"uniform vec2 length;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	vec4 scaled = model * aPos;\n"
		"	float theta = scaled.x / (length.x * radius);\n"
		"	float phi = scaled.y / (length.y * radius);\n"
		"	vec3 n_x = vec3(cos(theta), 0, -sin(theta));\n"
		"	vec3 n_y = vec3(0, cos(phi), -sin(phi));\n"
		"	scaled = vec4((radius + scaled.z) * normalize(cross(n_x, n_y)),"
		"		scaled.w);\n"
		"	scaled -= vec4(0, 0, radius, 0);\n"
		"	gl_Position = proj * view * scaled;\n"
		"	ourColor = aColor;"
		"}\0";

	return (source);
}

/**
 * Returns a vertex shader with a spherical warping transformation.
 *
 * @return	Vertex shader source code
 */
const char	*get_vshader_warping(void)
{
	const char	*source = "#version 330 core\n"
		"layout (location = 0) in vec4 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"uniform float radius;\n"
		"uniform vec2 length;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	vec4 scaled = model * aPos;\n"
		"	float theta = scaled.x / (length.x * radius);\n"
		"	float phi = scaled.y / (length.y * radius);\n"
		"	scaled = vec4("
		"		(radius + scaled.z) * sin(theta),"
		"		(radius + scaled.z) * sin(phi),"
		"		(radius + scaled.z) *"
		"			sqrt(pow(cos(theta), 2.) - pow(sin(phi), 2.)) - radius,"
		"		scaled.w);\n"
		"	gl_Position = proj * view * scaled;\n"
		"	ourColor = aColor;"
		"}\0";

	return (source);
}
