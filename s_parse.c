/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:59:17 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 14:27:29 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf			*null_pointer(t_pf *fm, t_buf *temp)
{
	size_t	i;
	char	*str;

	str = "(null)";
	fm->prec += fm->prec == 0 ? 7 : 0;
	i = 6;
	if (i + 1 > fm->prec)
		i = fm->prec > 0 ? fm->prec - 1 : i;
	fm->prec -= fm->prec > 0 ? 1 : 0;
	fm->width = i > fm->width ? i : fm->width;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	if (fm->null == 0 || fm->min == 1)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1 && fm->min == 0)
		ft_memset(temp->buff, '0', fm->width);
	!fm->min ? ft_memcpy(temp->buff + fm->width - i, str, i)
		: ft_memcpy(temp->buff, str, i);
	temp->size = fm->width;
	return (temp);
}

static t_buf	*ls_parse(va_list ap, t_pf *fm, t_buf *temp)
{
	wchar_t	*uni;
	uint8_t	*str;
	size_t	i;

	i = 0;
	if (!(uni = va_arg(ap, wint_t *)))
		return (null_pointer(fm, temp));
	if (!(str = unicode_s(uni, fm)))
		return (NULL);
	while (str[i])
		i++;
	i = fm->prec;
	fm->width = i > fm->width ? i : fm->width;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	if (fm->null == 0 || fm->min == 1)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1 && fm->min == 0)
		ft_memset(temp->buff, '0', fm->width);
	!fm->min ? ft_memcpy(temp->buff + fm->width - i, str, i)
		: ft_memcpy(temp->buff, str, i);
	free(str);
	temp->size = fm->width;
	return (temp);
}

static t_buf	*lc_parse(va_list ap, t_pf *fm, t_buf *temp)
{
	uint8_t		arr[4];
	size_t		len;
	uint32_t	c;

	len = 0;
	c = va_arg(ap, wint_t);
	unicode_c(c, base_ulen(c, 2, 0), arr, &len);
	fm->width = (fm->width > len) ? fm->width : len;
	temp->buff = ft_strnew(fm->width);
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->min)
		ft_memcpy(temp->buff, arr, len);
	else
		ft_memcpy(temp->buff + fm->width - len, arr, len);
	temp->size = fm->width;
	return (temp);
}

t_buf			*c_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	int		c;

	if ((format == 'C' || (fm->lenmode > 0 && format == 'c'))
			&& MB_CUR_MAX > 1)
		return (lc_parse(ap, fm, temp));
	c = (format != 'c' && format != 'C') ? format : va_arg(ap, int);
	fm->width = (fm->width > 1) ? fm->width : 1;
	if ((temp->buff = ft_strnew(fm->width)) == NULL)
		return (NULL);
	if (fm->null == 0)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1)
		ft_memset(temp->buff, '0', fm->width);
	if (fm->min == 1)
		temp->buff[0] = c;
	else
		temp->buff[fm->width - 1] = c;
	temp->size = fm->width;
	return (temp);
}

t_buf			*s_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	char	*str;
	size_t	i;

	if ((format == 'S' || fm->lenmode == 1) && MB_CUR_MAX > 1)
		return (ls_parse(ap, fm, temp));
	if ((str = va_arg(ap, char *)) == NULL)
		return (null_pointer(fm, temp));
	if ((i = ft_strlen(str)) + 1 > fm->prec)
		i = fm->prec > 0 ? fm->prec - 1 : i;
	fm->prec -= fm->prec > 0 ? 1 : 0;
	fm->width = i > fm->width ? i : fm->width;
	if (!(temp->buff = ft_strnew(fm->width)))
		return (NULL);
	if (fm->null == 0 || fm->min == 1)
		ft_memset(temp->buff, ' ', fm->width);
	else if (fm->null == 1 && fm->min == 0)
		ft_memset(temp->buff, '0', fm->width);
	!fm->min ? ft_memcpy(temp->buff + fm->width - i, str, i)
		: ft_memcpy(temp->buff, str, i);
	temp->size = fm->width;
	return (temp);
}
