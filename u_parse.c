/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:21:12 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/19 18:11:42 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fillint(t_pf *fm, t_buf *temp, size_t num)
{
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->prec > temp->size && (fm->min))
		ft_memset(temp->buff, '0', fm->prec - temp->size);
	else if (fm->prec > temp->size && !(fm->min))
		ft_memset(temp->buff + fm->width - fm->prec, '0',
				fm->prec - temp->size);
	if (temp->size && (fm->min))
		ft_itoa_base(num, 10, temp->buff + fm->prec - temp->size, fm);
	else if (temp->size && !(fm->min))
		ft_itoa_base(num, 10, temp->buff + fm->width - temp->size, fm);
}

t_buf			*u_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	size_t	num;

	fm->lenmode = format == 'U' ? 2 : fm->lenmode;
	num = getunsigned(ap, fm->lenmode);
	fm->null = fm->prec > 0 ? 0 : fm->null;
	temp->buff = NULL;
	if (!num && !(fm->width) && fm->prec == 1)
		return (temp);
	temp->size = (!num && fm->prec == 1) ? 0 : base_ulen(num, 10, fm->comma);
	fm->prec = temp->size + 1 > fm->prec ? temp->size : fm->prec - 1;
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	if ((temp->buff = ft_strnew(fm->width)) == NULL)
		return (NULL);
	fillint(fm, temp, num);
	temp->size = fm->width;
	return (temp);
}
