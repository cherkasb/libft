/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 20:14:03 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/19 16:00:40 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int			ft_vasprintf(char **str, const char *format, va_list ap)
{
	va_list	start;
	t_buf	*buflst;
	char	*strg;

	va_copy(start, ap);
	strg = (char *)format;
	buflst = NULL;
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(start);
	return (allocstring(buflst, str));
}

int			ft_vdprintf(int fd, const char *format, va_list ap)
{
	va_list	start;
	t_buf	*buflst;
	char	*strg;

	va_copy(start, ap);
	strg = (char *)format;
	buflst = NULL;
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(start);
	return (printbuff(buflst, fd));
}

int			ft_vprintf(const char *format, va_list ap)
{
	va_list	start;
	t_buf	*buflst;
	char	*strg;

	va_copy(start, ap);
	strg = (char *)format;
	buflst = NULL;
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(start);
	return (printbuff(buflst, 1));
}

int			ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	va_list	start;
	t_buf	*buflst;
	char	*strg;

	va_copy(start, ap);
	strg = (char *)format;
	buflst = NULL;
	if (!(printf_core(strg, &buflst, ap, start)))
		return (saveexit(buflst, ap, start));
	va_end(start);
	return (printtostring(buflst, str, size));
}
