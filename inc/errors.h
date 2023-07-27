/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:51:29 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/05 22:28:55 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define E_ARGS	"To use, pass the file name as argument:\n\t./fdf <filename>\n"
# define E_OPEN	"Failed to open file."
# define E_READ	"Failed to read file."
# define E_FORM	"Found wrong line length."
# define E_NULL	"No data dound."
# define E_ALOC	"Memory allocation failed."
# define E_OPGL	"OpenGL unable to create program."
# define E_HOOK	"Unable to hook loop events."

#endif
