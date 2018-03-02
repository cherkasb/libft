/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 22:12:17 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:35:17 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static void		fillint(t_pf *fm, t_buf *temp, char *str, size_t num)
{
	char	*s;

	s = "0x";
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->prec > num && fm->min)
		ft_memset(temp->buff + 2, '0', fm->prec - num - 2);
	else if (fm->prec > num && !(fm->min))
		ft_memset(temp->buff + fm->width - fm->prec, '0', fm->prec - num);
	if (num && fm->min)
		ft_memcpy(temp->buff + 2 + fm->prec - num - 2, str, num);
	else if (num && !(fm->min))
		ft_memcpy(temp->buff + fm->width - num, str, num);
	if (fm->min || fm->null)
		ft_memcpy(temp->buff, s, 2);
	else if (!fm->min)
		ft_memcpy(temp->buff + fm->width - fm->prec, s, 2);
}

t_buf			*p_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	char	*str;
	size_t	num;

	format = 'p';
	num = va_arg(ap, size_t);
	fm->null = fm->prec > 0 ? 0 : fm->null;
	str = ft_utoa_base(num, 16, 0);
	num = (!num && fm->prec == 1) ? 0 : ft_strlen(str);
	fm->prec = fm->prec > num + 1 ? fm->prec + 1 : num + 2;
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	fillint(fm, temp, str, num);
	temp->size = fm->width;
	return (temp);
}

int				n_parse(va_list ap, t_buf *bst, char **str)
{
	int		*len;

	len = va_arg(ap, int *);
	*len = 0;
	if (bst && bst->firstelem)
		*len = bst->firstelem->bufflen;
	(*str)++;
	return (1);
}
