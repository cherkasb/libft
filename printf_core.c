/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:15:25 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:40:23 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*g_colors[COLORSMAX][2] = {
	{"bold", "\x1b[1m"},
	{"faint", "\x1b[2m"},
	{"italic", "\x1b[3m"},
	{"red", "\x1b[31m"},
	{"green", "\x1b[32m"},
	{"yellow", "\x1b[33m"},
	{"blue", "\x1b[34m"},
	{"magenda", "\x1b[35m"},
	{"cyan", "\x1b[36m"},
	{"darkb", "\x1b[38;5;18;48;5;226m"},
	{"reset", "\x1b[0m"}};

static t_func	g_funcarr[MAXFORMATID] = {
	{'s', s_parse},
	{'c', c_parse},
	{'d', d_parse},
	{'o', o_parse},
	{'u', u_parse},
	{'x', x_parse},
	{'p', p_parse},
	{'x', b_parse},
	{'m', k_parse}};

int			saveexit(t_buf *delit, va_list ap, va_list start)
{
	t_buf	*lst;

	if (ap)
		va_end(ap);
	if (start)
		va_end(start);
	lst = (delit) ? delit->firstelem : NULL;
	while (lst)
	{
		delit = lst;
		lst = lst->next;
		if (delit->buff)
			free(delit->buff);
		free(delit);
	}
	return (-1);
}

static int	formatdata(char **str, t_buf **bst, va_list ap, va_list start)
{
	t_buf	temp;
	t_pf	format;
	ssize_t	i;

	(*str)++;
	if (**str == '\0')
		return (1);
	i = 0;
	changeposition(str, ap, start);
	checkflags(str, &format);
	width(str, &format, ap, start);
	getlength(str, &format);
	if ((i = lastpreparations(str, &format)) == -1 && **str != 'n')
	{
		if (!(c_parse(ap, &format, &temp, **str)))
			return (0);
	}
	else if (i > -1 && !(g_funcarr[i].func(ap, &format, &temp, **str)))
		return (0);
	else if (**str == 'n')
		return (n_parse(ap, *bst, str));
	if (!(writeformatted(temp.buff, temp.size, bst)))
		return (0);
	(*str)++;
	return (1);
}

static int	setcolor(char **str, t_buf **buflst, size_t *i, int *mode)
{
	size_t	j;

	j = 0;
	while (j < COLORSMAX)
	{
		if (ft_strstr(*str + *i + 1, g_colors[j][0]))
		{
			if (!(writestr(str, *str + *i, buflst, i)))
				return (0);
			while (*(*str + 1) && **str != '}')
				(*str)++;
			(*str)++;
			if (!(writeformatted(ft_strdup(g_colors[j][1]),
							ft_strlen(g_colors[j][1]), buflst)))
				return (0);
			*mode = 1;
			return (1);
		}
		j++;
	}
	(*i)++;
	return (1);
}

int			printf_core(char *strg, t_buf **buflst, va_list ap, va_list start)
{
	int		mode;
	size_t	i;

	mode = 0;
	i = 0;
	while (strg[i])
	{
		if (strg[i] == '{')
			if (!setcolor(&strg, buflst, &i, &mode))
				return (0);
		if (strg[i] == '%')
		{
			if (!(writestr(&strg, strg + i, buflst, &i)))
				return (0);
			if (!(formatdata(&strg, buflst, ap, start)))
				return (0);
		}
		else
			i++;
	}
	if (!(writestr(&strg, strg + i, buflst, &i)))
		return (0);
	if (mode && !(writeformatted(ft_strdup("\x1b[0m"), 4, buflst)))
		return (0);
	return (1);
}
