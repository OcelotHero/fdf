/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:48:52 by rraharja          #+#    #+#             */
/*   Updated: 2023/07/06 22:31:52 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * Cleans up any allocated resources and terminates opened window. Printing
 * error message if any error occurs.
 *
 * @param	fdf		fdf struct where allocated memory is stored
 * @param	error	Error code
 * @return	Either the application encounters errors or successfully concludes
 */
int	cleanup(t_fdf *fdf, int error)
{
	if (fdf && fdf->map.data)
		free(fdf->map.data);
	if (fdf && fdf->mlx)
		mlx_terminate(fdf->mlx);
	if (error == 1)
		ft_printf(E_ARGS);
	else if (error == 2)
		ft_printf(E_OPEN);
	else if (error == 3)
		ft_printf(E_READ);
	else if (error == 4)
		ft_printf(E_FORM);
	else if (error == 5)
		ft_printf(E_NULL);
	else if (error == 6)
		ft_printf(E_ALOC);
	else if (error == 7)
		ft_printf(E_OPGL);
	else if (error == 8)
		ft_printf(E_HOOK);
	else if (error == 9)
		ft_printf(mlx_strerror(mlx_errno));
	return (error != 0);
}
