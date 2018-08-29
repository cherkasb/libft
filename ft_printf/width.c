/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 18:58:11 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:29:57 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	precwidth_star(char **str, va_list start, va_list cpy)
{
	ssize_t		i;
	ssize_t		save;

	i = 0;
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
		i++;
	if ((*str)[i] != '$' || i == 0)
		return (0);
	save = i;
	i = ft_atoi(*str);
	i = i < 0 ? -i : i;
	va_copy(cpy, start);
	while (i > 1)
	{
		va_arg(cpy, size_t);
		i--;
	}
	*str += save;
	return (1);
}

static void	precision(char **str, t_pf *format, va_list ap, va_list start)
{
	va_list	cpy;
	ssize_t	i;

	format->prec = 0;
	if (**str != '.')
		return ;
	(*str)++;
	i = ft_atoi(*str) + 1;
	if (**str == '*')
	{
		(*str)++;
		if (!precwidth_star(str, start, cpy))
			i = va_arg(ap, int) + 1;
		else
		{
			i = va_arg(cpy, int) + 1;
			va_end(cpy);
		}
	}
	while (**str == '*' || (**str >= '0' && **str <= '9') || **str == '$' ||
		**str == '-' || **str == '+')
		(*str)++;
	format->prec = i < 0 ? 0 : i;
}

void		width(char **str, t_pf *format, va_list ap, va_list start)
{
	va_list	cpy;
	ssize_t	i;

	format->width = 0;
	i = ft_atoi(*str);
	while (**str >= '0' && **str <= '9')
		(*str)++;
	if (**str == '*')
	{
		(*str)++;
		if (!precwidth_star(str, start, cpy))
			i = va_arg(ap, int);
		else
		{
			i = va_arg(cpy, int);
			va_end(cpy);
		}
	}
	while (**str == '*' || (**str >= '0' && **str <= '9') || **str == '$' ||
		**str == '-' || **str == '+')
		(*str)++;
	format->min = i < 0 ? 1 : format->min;
	format->width = i < 0 ? -i : i;
	precision(str, format, ap, start);
}
