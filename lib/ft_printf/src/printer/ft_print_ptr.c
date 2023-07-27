/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:08:33 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/23 15:27:34 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_ptr(unsigned long long ptr, t_pconfig *config)
{
	if (ptr == 0)
		return (ft_print_null(config, 1));
	config->form = 1;
	config->conv = 'x';
	return (ft_print_nb_base(ptr, config));
}
