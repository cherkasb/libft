/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 20:14:03 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:36:54 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int			ft_asprintf(char **str, const char *format, ...)
{
	va_list	ap;
	va_list start;
	t_buf	*buflst;
	char	*strg;

	strg = (char *)format;
	buflst = NULL;
	va_start(ap, format);
	va_copy(start, ap);
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(ap);
	va_end(start);
	return (allocstring(buflst, str));
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	va_list start;
	t_buf	*buflst;
	char	*strg;

	strg = (char *)format;
	buflst = NULL;
	va_start(ap, format);
	va_copy(start, ap);
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(ap);
	va_end(start);
	return (printbuff(buflst, fd));
}

int			ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	va_list start;
	t_buf	*buflst;
	char	*strg;

	strg = (char *)format;
	buflst = NULL;
	va_start(ap, format);
	va_copy(start, ap);
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(ap);
	va_end(start);
	return (printtostring(buflst, str, size));
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	va_list start;
	t_buf	*buflst;
	char	*strg;

	strg = (char *)format;
	buflst = NULL;
	va_start(ap, format);
	va_copy(start, ap);
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(ap);
	va_end(start);
	return (printbuff(buflst, 1));
}
