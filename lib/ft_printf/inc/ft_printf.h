/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraharja <rraharja@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:09:30 by rraharja          #+#    #+#             */
/*   Updated: 2022/10/20 19:09:30 by rraharja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*------ Macros ------*/
# define FLAG " -+0#"
# define BASE "0123456789abcdef"
# define CONVERSION "cspdiuxX%"

# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

/*------ Configurations ------*/
typedef struct s_pconfig {
	bool	form;
	char	padding;
	char	pos_prefix;
	int		width;
	int		precision;
	char	conv;
}	t_pconfig;

/*------ Parser functions ------*/
size_t		ft_parse(const char **format, va_list args);
t_pconfig	*ft_parse_config(const char **format);

/*------ Printer functions ------*/
size_t		ft_print_percent(t_pconfig *config);
size_t		ft_print_null(t_pconfig *config, bool is_ptr);
size_t		ft_print_char(const char c, t_pconfig *config);
size_t		ft_print_nb_base(long long n, t_pconfig *config);
size_t		ft_print_ptr(unsigned long long ptr, t_pconfig *config);
size_t		ft_print_str(const char *str, char padding, t_pconfig *config);
size_t		ft_print_none(t_pconfig *config, const char **format, char *start);

/*------ Utils functions ------*/
int			ft_isdigit(int c);
bool		ft_contains(const char *s, char c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_pos_atoi(const char **str);

/*------ ft_printf function ------*/
int			ft_printf(const char *format, ...);

#endif
