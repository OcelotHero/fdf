/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:08:03 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/24 20:22:58 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_str(const char *str, char padding, t_pconfig *config)
{
	int	len;

	len = -1;
	if (!str)
		return (ft_print_null(config, 0));
	if (config->precision == -1 || config->precision > (int) ft_strlen(str))
		config->precision = ft_strlen(str);
	if (config->width < config->precision)
		config->width = config->precision;
	if (config->padding == '-')
	{
		while (++len < config->precision && *str)
			write(1, str++, 1);
		while (++len <= config->width)
			write(1, " ", 1);
	}
	else
	{
		while (++len < config->width - config->precision)
			write(1, &padding, 1);
		while (++len <= config->width && *str)
			write(1, str++, 1);
	}
	free(config);
	return (len - 1);
}
