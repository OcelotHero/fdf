/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:13:21 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 19:13:21 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Checks for whitespace character.
 *
 * @param	c	Character to check
 * @return	Whether the given character is a whitespace
 */
bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

/**
 * Checks for valid fdf-file character.
 *
 * @param	c	Character to check
 * @return	Whether the given character is a valid character
 */
bool	is_valid(char c)
{
	return ((c >= '0' && c <= '9') || c == ',' || c == 'x' || c == 'X'
		|| (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

/**
 * Converts the given integer value into vec4 RGBA format
 *
 * @param	color	Integer representation of an RGB color
 * @return	The given color in vec4 RGBA format
 */
t_vec4	int_to_col(int color)
{
	return ((t_vec4){{(color >> 16 & 0xff) / 255.0f,
			(color >> 8 & 0xff) / 255.0f, (color & 0xff) / 255.0f, 1.0f}});
}
