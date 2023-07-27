/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:30:45 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/06 21:02:41 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

# include "libft.h"
# include "maths.h"
# include "types.h"
# include "utils.h"

bool	is_space(char c);
bool	is_valid(char c);
t_vec4	int_to_col(int color);

int		parse_file(const char *filename, t_fdf *fdf);

#endif
