/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:42:55 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:35:57 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		base_ulen(size_t n, int base, size_t sep)
{
	size_t	len;
	size_t	bs;

	if (n == 0)
		return (1);
	bs = (size_t)base;
	len = 0;
	while (n)
	{
		n /= bs;
		len++;
	}
	if (sep > 0)
		len += (len % sep == 0) ? len / sep - 1 : len / sep;
	return (len);
}

char		*ft_utoa_base(size_t n, int base, int big)
{
	char		*bases;
	ssize_t		len;
	static char	fin[22];

	ft_bzero(fin, 22);
	bases = !big ? "0123456789abcdef" : "0123456789ABCDEF";
	len = base_ulen(n, base, 0) - 1;
	while (len >= 0)
	{
		fin[len] = bases[n % (size_t)base];
		n /= (size_t)base;
		len--;
	}
	return (fin);
}

static void	ft_comma_base(size_t n, int base, char *fin, size_t sep)
{
	char		*bases;
	ssize_t		len;
	ssize_t		count;

	count = 1;
	bases = "0123456789abcdef";
	len = base_ulen(n, base, sep);
	while (count <= len)
	{
		if (count % (sep + 1) == 0)
		{
			fin[len - count] = ',';
			count++;
		}
		fin[len - count] = bases[n % (size_t)base];
		n /= (size_t)base;
		count++;
	}
}

void		ft_itoa_base(size_t n, int base, char *fin, t_pf *fm)
{
	char		*bases;
	ssize_t		len;
	size_t		sep;

	sep = fm->comma;
	if (sep)
	{
		ft_comma_base(n, base, fin, sep);
		return ;
	}
	bases = "0123456789abcdef";
	len = base_ulen(n, base, 0) - 1;
	while (len >= 0)
	{
		fin[len] = bases[n % (size_t)base];
		n /= (size_t)base;
		len--;
	}
}
