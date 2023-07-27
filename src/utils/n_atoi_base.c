/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_atoi_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:44:56 by rraharja          #+#    #+#             */
/*   Updated: 2023/03/30 22:34:39 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * Returns the index of the character c within the given string str. Returns -1
 * if c is not a member of str
 *
 * @param	c	The character to look for
 * @param	str	The input string
 * @return	The index of c within str, -1 otherwise
 */
static int	index_of(const char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (-1 * (str[i] == '\0') + i * (str[i] != '\0'));
}

/**
 * A modified atoi_base, storing the result to val parameter and returns the
 * number of characters parsed before stopping.
 *
 * @param	str		The input string
 * @param	base	The string containing the characters representing the
 * 					value
 * @param	radix	The base numbering system of the input number
 * @param	val		Pointer to store the resulting value
 * @return	The number of characters parsed before stopping
 */
int	n_atoi_base(const char *str, char *base, int radix, int *val)
{
	int					i;
	int					idx;
	int					sign;
	unsigned long long	total;

	i = 0;
	total = *val;
	while (is_space(str[i]))
		i++;
	sign = (str[i] == '+') - (str[i] == '-');
	i += (str[i] == '+' || str[i] == '-');
	sign = !sign + (sign != 0) * sign;
	idx = index_of(ft_tolower(str[i]), base);
	while (idx != -1 && idx < radix)
	{
		total *= radix;
		total += idx;
		idx = index_of(ft_tolower(str[++i]), base);
	}
	*val = sign * total;
	return (i);
}
