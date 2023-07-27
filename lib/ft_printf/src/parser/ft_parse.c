/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:09:10 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/23 15:27:54 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_parse(const char **format, va_list args)
{
	char		*start;
	t_pconfig	*config;

	if (!**format)
		return (0);
	start = (char *) *format;
	config = ft_parse_config(format);
	if (!config)
		return (0);
	if (!ft_contains(CONVERSION, config->conv))
		return (ft_print_none(config, format, start));
	(*format)++;
	if (config->conv == '%')
		return (ft_print_percent(config));
	if (config->conv == 'c')
		return (ft_print_char(va_arg(args, int), config));
	if (config->conv == 's')
		return (ft_print_str(va_arg(args, char *), ' ', config));
	if (config->conv == 'd' || config->conv == 'i')
		return (ft_print_nb_base(va_arg(args, int), config));
	if (config->conv == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long long), config));
	return (ft_print_nb_base(va_arg(args, unsigned int), config));
}
