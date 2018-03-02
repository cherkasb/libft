/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:33:00 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/19 16:01:28 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

size_t	getsigned(va_list ap, int intlen, int *min)
{
	ssize_t	a;
	size_t	z;

	*min = 0;
	a = (intlen == -2) ? (char)va_arg(ap, int) : 0;
	if (intlen == -1)
		a = (short)va_arg(ap, int);
	else if (intlen == 0)
		a = va_arg(ap, int);
	else if (intlen == 1)
		a = va_arg(ap, long);
	else if (intlen == 2)
		a = va_arg(ap, long long);
	else if (intlen == 3)
		a = va_arg(ap, intmax_t);
	else if (intlen == 4)
		a = va_arg(ap, ssize_t);
	else if (intlen == 5)
		a = va_arg(ap, intptr_t);
	else if (intlen == 6)
		a = va_arg(ap, int);
	*min = (a < 0) ? 1 : 0;
	z = (a < 0) ? -a : a;
	return (z);
}

size_t	getunsigned(va_list ap, int intlen)
{
	size_t	a;

	a = (intlen == -2) ? (unsigned char)va_arg(ap, int) : 0;
	if (intlen == -1)
		a = (unsigned short)va_arg(ap, int);
	else if (intlen == 0)
		a = va_arg(ap, unsigned int);
	else if (intlen == 1)
		a = va_arg(ap, unsigned long);
	else if (intlen == 2)
		a = va_arg(ap, unsigned long long);
	else if (intlen == 3)
		a = va_arg(ap, uintmax_t);
	else if (intlen == 4)
		a = va_arg(ap, size_t);
	else if (intlen == 5)
		a = va_arg(ap, uintptr_t);
	else if (intlen == 6)
		a = va_arg(ap, uint64_t);
	return (a);
}
