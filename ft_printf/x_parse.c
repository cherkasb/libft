/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:25:08 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:28:09 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fm->extra used here to save information about small 'x' or big 'X'
*/

#include "ft_printf.h"

static void		ft_itoa_base_x(size_t n, int base, char *fin, int big)
{
	char		*bases;
	ssize_t		len;

	bases = big ? "0123456789ABCDEF" : "0123456789abcdef";
	len = base_ulen(n, base, 0) - 1;
	while (len >= 0)
	{
		fin[len] = bases[n % (size_t)base];
		n /= (size_t)base;
		len--;
	}
}

static void		fillint(t_pf *fm, t_buf *temp, size_t num)
{
	char	*s;

	s = fm->extra ? "0X" : "0x";
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->prec > temp->size && fm->min)
		ft_memset(temp->buff + fm->sharp * 2, '0', fm->prec - temp->size);
	else if (fm->prec > temp->size && !(fm->min))
		ft_memset(temp->buff + fm->width - fm->prec, '0',
				fm->prec - temp->size);
	if (temp->size && fm->min)
		ft_itoa_base_x(num, 16,
				temp->buff + fm->sharp * 2 + fm->prec - temp->size, fm->extra);
	else if (temp->size && !(fm->min))
		ft_itoa_base_x(num, 16, temp->buff + fm->width - temp->size, fm->extra);
	if (fm->sharp && (fm->min || fm->null))
		ft_memcpy(temp->buff, s, 2);
	else if (fm->sharp && !fm->min)
		ft_memcpy(temp->buff + fm->width - fm->prec - 2, s, 2);
}

t_buf			*x_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	size_t	num;

	fm->extra = format == 'X' ? 1 : 0;
	num = getunsigned(ap, fm->lenmode);
	temp->buff = NULL;
	fm->null = fm->prec > 0 ? 0 : fm->null;
	if (!num && !(fm->width) && fm->prec == 1)
		return (temp);
	fm->sharp = !num ? 0 : fm->sharp;
	temp->size = (!num && fm->prec == 1) ? 0 : base_ulen(num, 16, 0);
	fm->prec = fm->prec > temp->size + 1 ? fm->prec - 1 : temp->size;
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	fm->width += fm->width - 1 == fm->prec ? fm->sharp : 0;
	fm->width += fm->width == fm->prec ? fm->sharp * 2 : 0;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	fillint(fm, temp, num);
	temp->size = fm->width;
	return (temp);
}
