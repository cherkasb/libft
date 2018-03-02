/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:12:32 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:34:44 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static void		fillint(t_pf *fm, t_buf *temp, size_t num)
{
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->prec > temp->size && fm->min)
		ft_memset(temp->buff + fm->sharp, '0', fm->prec - temp->size);
	else if (fm->prec > temp->size && !fm->min)
		ft_memset(temp->buff + fm->width - fm->prec, '0',
				fm->prec - temp->size);
	if (temp->size && fm->min)
		ft_itoa_base(num, 8,
				temp->buff + fm->sharp + fm->prec - temp->size, fm);
	else if (temp->size && !fm->min)
		ft_itoa_base(num, 8, temp->buff + fm->width - temp->size, fm);
	if (fm->sharp && fm->min)
		temp->buff[0] = '0';
	else if (!fm->min && fm->sharp)
		temp->buff[fm->width - temp->size - 1] = '0';
}

t_buf			*o_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	size_t	num;

	fm->comma = 0;
	fm->lenmode = format == 'O' ? 2 : fm->lenmode;
	num = getunsigned(ap, fm->lenmode);
	fm->null = fm->prec > 0 ? 0 : fm->null;
	temp->buff = NULL;
	if (!num && !(fm->width) && fm->prec == 1 && !fm->sharp)
		return (temp);
	if ((temp->size = base_ulen(num, 8, fm->comma)) + 1 < fm->prec ||
			(!num && fm->prec != 1))
		fm->sharp = 0;
	if (!num && fm->prec == 1)
		temp->size = 0;
	fm->prec = fm->prec > temp->size + 1 ? fm->prec - 1 : temp->size;
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	fm->width += (fm->width == temp->size && fm->sharp) ? 1 : 0;
	if ((temp->buff = ft_strnew(fm->width)) == NULL)
		return (NULL);
	fillint(fm, temp, num);
	temp->size = fm->width;
	return (temp);
}

static size_t	getprecision(int lenmode)
{
	size_t	i;

	i = 0;
	if (lenmode == -2)
		i = sizeof(unsigned char);
	else if (lenmode == -1)
		i = sizeof(unsigned short);
	else if (lenmode == 0)
		i = sizeof(unsigned);
	else if (lenmode == 1)
		i = sizeof(unsigned long);
	else if (lenmode == 2)
		i = sizeof(unsigned long long);
	else if (lenmode == 3)
		i = sizeof(uintmax_t);
	else if (lenmode == 4)
		i = sizeof(size_t);
	else if (lenmode == 5)
		i = sizeof(uintptr_t);
	else if (lenmode == 6)
		i = sizeof(uint64_t);
	i = i * 10 - 1;
	return (i);
}

static void		fillbinary(char *fin, size_t num, ssize_t prec)
{
	ssize_t	count;

	count = 1;
	while (num > 0)
	{
		if (count % 5 == 0)
		{
			fin[prec - count] = ' ';
			count++;
		}
		fin[prec - count] = (num % 2) + '0';
		num /= 2;
		count++;
	}
	while (count <= prec)
	{
		if (count % 5 == 0)
		{
			fin[prec - count] = ' ';
			count++;
		}
		fin[prec - count] = '0';
		count++;
	}
}

t_buf			*b_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	size_t	num;
	ssize_t	i;

	format = 'b';
	num = va_arg(ap, size_t);
	fm->prec = getprecision(fm->lenmode);
	fm->width = fm->width > fm->prec ? fm->width : fm->prec;
	i = base_ulen(num, 2, 4);
	i = (size_t)i > fm->prec ? fm->prec - 1 : i - 1;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	ft_memset(temp->buff, ' ', fm->width - fm->prec);
	fillbinary(temp->buff + fm->width - fm->prec, num, fm->prec);
	temp->size = fm->width;
	return (temp);
}
