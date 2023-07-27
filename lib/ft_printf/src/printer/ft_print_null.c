/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:06:33 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/24 20:25:35 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_null(t_pconfig *config, bool is_ptr)
{
	if (is_ptr)
		return (ft_print_str("0x0", ' ', config));
	return (ft_print_str("(null)", ' ', config));
}
