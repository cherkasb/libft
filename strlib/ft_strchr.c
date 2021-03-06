/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:06:43 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/22 12:02:45 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (2)
	{
		if (s[i] == c || s[i] == '\0')
			break ;
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}
