/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:07:43 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/23 15:27:09 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_char(const char c, t_pconfig *config)
{
	int	len;

	len = 0;
	if (config->width < 0)
		config->width = 1;
	if (config->padding == '-')
		write(1, &c, 1);
	while (++len < config->width)
		write(1, " ", 1);
	if (config->padding != '-')
		write(1, &c, 1);
	free(config);
	return (len);
}
