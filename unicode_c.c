/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:13:36 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/19 18:16:28 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const unsigned	g_mask[3] = {49280, 14712960, 4034953344};

static size_t	arraylength(wchar_t *arr)
{
	size_t	k;
	size_t	i;

	i = 0;
	while (arr && *arr)
	{
		k = base_ulen(*arr, 2, 0);
		if (k <= 7)
			k = 1;
		else if (k <= 11)
			k = 2;
		else if (k <= 16)
			k = 3;
		else
			k = 4;
		i += k;
		arr++;
	}
	return (i);
}

void			unicode_c(unsigned v, size_t size, uint8_t *buff, size_t *len)
{
	*len = 1;
	if (size <= 7)
		buff[0] = v;
	else if (size <= 11)
	{
		buff[0] = (g_mask[0] >> 8) | (((v >> 6) << 27) >> 27);
		buff[1] = ((g_mask[0] << 24) >> 24) | ((v << 26) >> 26);
		*len = 2;
	}
	else if (size <= 16)
	{
		buff[0] = (g_mask[1] >> 16) | (((v >> 12) << 28) >> 28);
		buff[1] = ((g_mask[1] << 16) >> 24) | (((v >> 6) << 26) >> 26);
		buff[2] = ((g_mask[1] << 24) >> 24) | ((v << 26) >> 26);
		*len = 3;
	}
	else
	{
		buff[0] = (g_mask[2] >> 24) | (((v >> 18) << 29) >> 29);
		buff[1] = ((g_mask[2] << 8) >> 24) | (((v >> 12) << 26) >> 26);
		buff[2] = ((g_mask[2] << 16) >> 24) | (((v >> 6) << 26) >> 26);
		buff[3] = ((g_mask[2] << 24) >> 24) | ((v << 26) >> 26);
		*len = 4;
	}
}

uint8_t			*unicode_s(wint_t *v, t_pf *fm)
{
	uint8_t	temp[4];
	uint8_t	*str;
	size_t	i;
	size_t	n;

	i = arraylength(v);
	if (i + 1 > fm->prec)
		i = fm->prec > 0 ? fm->prec - 1 : i;
	fm->prec = i;
	if (!(str = (uint8_t *)ft_strnew(i)))
		return (NULL);
	i = 0;
	while (v && *v)
	{
		unicode_c(*v, base_ulen(*v, 2, 0), temp, &n);
		if (n + i > fm->prec)
			break ;
		ft_memcpy(str + i, temp, n);
		i += n;
		v++;
	}
	fm->prec = i;
	return (str);
}
