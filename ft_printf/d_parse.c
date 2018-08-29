/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:59:17 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/19 18:10:43 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fm->extra saves information about number's negative status
*/

#include "ft_printf.h"

static void		width_prec(t_pf *fm, t_buf *temp, size_t num)
{
	int		sep;

	sep = (fm->space || fm->plus || fm->extra) ? 1 : 0;
	if (fm->null)
		ft_memset(temp->buff, '0', fm->width);
	else if (!fm->null)
		ft_memset(temp->buff, ' ', fm->width);
	if (fm->prec > temp->size && fm->min)
		ft_memset(temp->buff + sep, '0', fm->prec - temp->size);
	else if (fm->prec > temp->size && !fm->min)
		ft_memset(temp->buff + fm->width - fm->prec, '0',
				fm->prec - temp->size);
	if (temp->size && fm->min)
		ft_itoa_base(num, 10, temp->buff + sep + fm->prec - temp->size, fm);
	else if (temp->size && !fm->min)
		ft_itoa_base(num, 10, temp->buff + fm->width - temp->size, fm);
}

static void		fillint(t_pf *fm, t_buf *temp, size_t num)
{
	width_prec(fm, temp, num);
	if (fm->extra && (fm->min || fm->null))
		temp->buff[0] = '-';
	else if (fm->space && fm->min)
		temp->buff[0] = ' ';
	else if (!fm->extra && (fm->min || fm->null) && fm->plus)
		temp->buff[0] = '+';
	else if (fm->extra && !fm->min && !fm->null)
		temp->buff[fm->width - fm->prec - 1] = '-';
	else if (!fm->extra && fm->plus && !fm->min && !fm->null)
		temp->buff[fm->width - fm->prec - 1] = '+';
	else if (fm->space && !fm->min)
		temp->buff[0] = ' ';
}

t_buf			*d_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	size_t	num;

	fm->lenmode = format == 'D' ? 1 : fm->lenmode;
	num = getsigned(ap, fm->lenmode, &fm->extra);
	fm->null = fm->prec > 0 ? 0 : fm->null;
	fm->space = fm->extra ? 0 : fm->space;
	temp->buff = NULL;
	if (!num && !(fm->width) && fm->prec == 1 && !fm->space && !fm->plus)
		return (temp);
	temp->size = (!num && fm->prec == 1) ? 0 : base_ulen(num, 10, fm->comma);
	fm->prec = temp->size + 1 > fm->prec ? temp->size : fm->prec - 1;
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	fm->width += (fm->width == fm->prec &&
			(fm->extra || fm->plus || fm->space)) ? 1 : 0;
	if ((temp->buff = ft_strnew(fm->width)) == NULL)
		return (NULL);
	fillint(fm, temp, num);
	temp->size = fm->width;
	return (temp);
}
