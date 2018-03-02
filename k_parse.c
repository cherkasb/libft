/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:48:39 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/21 16:11:41 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <time.h>

t_buf	*k_parse(va_list ap, t_pf *fm, t_buf *temp, char format)
{
	time_t		timer;
	struct tm	*tm_info;
	char		*str;

	if (format || fm)
		;
	timer = va_arg(ap, time_t);
	tm_info = localtime(&timer);
	str = asctime(tm_info);
	temp->size = ft_strlen(str) - 1;
	str[temp->size] = '\0';
	if (!(temp->buff = ft_strdup(str)))
		return (NULL);
	return (temp);
}
