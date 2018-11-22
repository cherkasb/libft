/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:07:55 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/14 16:02:48 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	fraction_part(const char *str)
{
	double		power;
	double		val;

	power = 1.0;
	val = 0.0;
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		val = val * 10.0 + (*str - '0');
		power *= 10;
		str++;
	}
	return (val / power);
}

float			ft_atof(const char *str)
{
	int				min;
	double			sum;

	sum = 0;
	min = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		min = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		sum = sum * 10.0 + (*str - '0');
		str++;
	}
	return (min * (sum + fraction_part(str)));
}
