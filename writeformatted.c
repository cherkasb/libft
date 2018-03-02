/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writeformatted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 14:08:43 by bcherkas          #+#    #+#             */
/*   Updated: 2018/02/18 15:05:16 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		writeformatted(char *buff, size_t size, t_buf **buflst)
{
	if (!buff || !size)
		return (1);
	if (*buflst == NULL)
	{
		if (!(*buflst = (t_buf*)malloc(sizeof(t_buf))))
			return (0);
		(*buflst)->firstelem = *buflst;
		(*buflst)->bufflen = 0;
	}
	else
	{
		if (!((*buflst)->next = (t_buf*)malloc(sizeof(t_buf))))
			return (0);
		(*buflst)->next->firstelem = (*buflst)->firstelem;
		*buflst = (*buflst)->next;
	}
	(*buflst)->next = NULL;
	(*buflst)->size = size;
	(*buflst)->buff = buff;
	(*buflst)->firstelem->bufflen += (*buflst)->size;
	return (1);
}

int		writestr(char **str, char *save, t_buf **buflst, size_t *i)
{
	*i = 0;
	if (save == *str)
		return (1);
	if (*buflst == NULL)
	{
		if (!(*buflst = (t_buf*)malloc(sizeof(t_buf))))
			return (0);
		(*buflst)->firstelem = *buflst;
		(*buflst)->bufflen = 0;
	}
	else
	{
		if (!((*buflst)->next = (t_buf*)malloc(sizeof(t_buf))))
			return (0);
		(*buflst)->next->firstelem = (*buflst)->firstelem;
		*buflst = (*buflst)->next;
	}
	(*buflst)->next = NULL;
	(*buflst)->size = save - *str;
	(*buflst)->buff = ft_strnew((*buflst)->size);
	ft_memcpy((*buflst)->buff, *str, (*buflst)->size);
	(*buflst)->firstelem->bufflen += (*buflst)->size;
	*str = save;
	return (1);
}

int		printbuff(t_buf *buflst, int fd)
{
	char	*save;
	char	*done;
	t_buf	*now;
	int		len;

	if (!(now = buflst))
		return (0);
	buflst = buflst->firstelem;
	len = buflst->bufflen;
	if (!(done = ft_strnew(len)))
		return (saveexit(buflst, NULL, NULL));
	save = done;
	while (buflst)
	{
		ft_memcpy(done, buflst->buff, buflst->size);
		if (buflst->buff)
			free(buflst->buff);
		done += buflst->size;
		now = buflst;
		buflst = buflst->next;
		free(now);
	}
	write(fd, save, len);
	free(save);
	return (len);
}

int		printtostring(t_buf *buflst, char *str, size_t max)
{
	t_buf	*now;
	int		len;

	if (!buflst)
		return (0);
	now = buflst;
	buflst = buflst->firstelem;
	len = (buflst->bufflen > max && max > 0) ? max : buflst->bufflen;
	while (buflst)
	{
		ft_memcpy(str, buflst->buff, buflst->size);
		if (buflst->buff)
			free(buflst->buff);
		str += buflst->size;
		now = buflst;
		buflst = buflst->next;
		free(now);
	}
	return (len);
}

int		allocstring(t_buf *buflst, char **str)
{
	t_buf	*now;
	int		len;

	if (!str)
		return (-1);
	if (!buflst)
		return (0);
	now = buflst;
	buflst = buflst->firstelem;
	len = buflst->bufflen;
	if (!((*str) = ft_strnew(len)))
		return (saveexit(buflst, NULL, NULL));
	while (buflst)
	{
		ft_memcpy((*str), buflst->buff, buflst->size);
		if (buflst->buff)
			free(buflst->buff);
		(*str) += buflst->size;
		now = buflst;
		buflst = buflst->next;
		free(now);
	}
	return (len);
}
