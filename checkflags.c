/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:15:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/20 15:59:14 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	lenmode: 0 - nothing, 1 - h, 2 - hh, 3 - l, 4 - ll, 5 - j, 6 - z
*/

#include "ft_printf.h"
#include <stdarg.h>

void	getlength(char **str, t_pf *format)
{
	format->lenmode = 0;
	if (str[0][0] == 'h' && str[0][1] != 'h')
		format->lenmode = -1;
	else if (str[0][0] == 'h' && str[0][1] == 'h')
		format->lenmode = -2;
	else if (str[0][0] == 'l' && str[0][1] != 'l')
		format->lenmode = 1;
	else if (str[0][0] == 'l' && str[0][1] == 'l')
		format->lenmode = 2;
	else if (**str == 'j')
		format->lenmode = 3;
	else if (**str == 'z')
		format->lenmode = 4;
	else if (**str == 't')
		format->lenmode = 5;
	else if (**str == 'L')
		format->lenmode = 6;
	while (**str == 'l' || **str == 'h' || **str == 'j' || **str == 'z' ||
			**str == 't' || **str == 'L' || **str == '$' || **str == ' ')
		(*str)++;
}

void	changeposition(char **str, va_list ap, va_list start)
{
	ssize_t		i;
	ssize_t		save[2];

	save[0] = 0;
	save[1] = 0;
	i = 0;
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
		i++;
	if (i == 0 && (*str)[i] == '*')
		save[0] = i++;
	if ((*str)[i] != '$' || i == 0)
		return ;
	save[1] = i;
	i = save[0] ? va_arg(ap, int) : ft_atoi(*str);
	i = i < 0 ? -i : i;
	va_end(ap);
	va_copy(ap, start);
	while (i > 1)
	{
		va_arg(ap, size_t);
		i--;
	}
	*str += save[1] + 1;
}

int		lastpreparations(char **str, t_pf *format)
{
	char	*formatlist;
	int		i;

	format->null = format->min ? 0 : format->null;
	format->space = format->plus ? 0 : format->space;
	i = 0;
	formatlist = "scdouxpbk";
	while (formatlist[i] != **str &&
			formatlist[i] != **str + 32 && i < MAXFORMATID)
		i++;
	if (**str == 'i')
		i = 2;
	i = (i == MAXFORMATID) ? -1 : i;
	return (i);
}

void	checkflags(char **str, t_pf *format)
{
	format->sharp = 0;
	format->null = 0;
	format->min = 0;
	format->plus = 0;
	format->space = 0;
	format->comma = 0;
	while (**str == '#' || **str == '0' || **str == '-' ||
		**str == '+' || **str == ' ' || **str == '\'')
	{
		if (**str == '#')
			format->sharp = 1;
		else if (**str == '0')
			format->null = 1;
		else if (**str == '-')
			format->min = 1;
		else if (**str == '+')
			format->plus = 1;
		else if (**str == ' ')
			format->space = 1;
		else if (**str == '\'')
			format->comma = 3;
		(*str)++;
	}
}
