/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:37:02 by bcherkas          #+#    #+#             */
/*   Updated: 2018/11/22 18:02:56 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int	inttostr(int x, char str[], int d)
{
	int	i;

	i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	ft_strrev(str + i);
	str[i] = '\0';
	return (i);
}

void		ftoa(float n, char *res, int afterpoint)
{
	int		ipart;
	float	fpart;
	int		i;

	ipart = (int)n;
	fpart = n - (float)ipart;
	i = inttostr(ipart, res, 0);
	if (afterpoint != 0)
	{
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		inttostr((int)fpart, res + i + 1, afterpoint);
	}
}
