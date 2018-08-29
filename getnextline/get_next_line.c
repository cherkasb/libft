/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 15:12:19 by bcherkas          #+#    #+#             */
/*   Updated: 2018/01/13 19:42:37 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			get_buff(t_bufflist *lst, char **line, size_t *linelen)
{
	size_t		i;
	int			res;
	char		*newline;

	i = 0;
	res = 0;
	while (lst && lst->buff[i] && lst->buff[i] != '\n' && i < BUFF_SIZE)
		i++;
	if (i < BUFF_SIZE && (lst->buff[i] == '\n' || (*linelen > 0 && !i)))
		res = 1;
	newline = ft_strnew(*linelen + i);
	*linelen += i;
	if (line && *line)
		ft_strcpy(newline, *line);
	ft_strncat(newline, lst->buff, i);
	if (*line)
		free(*line);
	*line = newline;
	ft_memcpy(lst->buff, lst->buff + i, BUFF_SIZE - i);
	ft_bzero(lst->buff + BUFF_SIZE - i, i);
	return (res);
}

void		delelem(t_bufflist **list, t_bufflist **start, char **line)
{
	t_bufflist	*temp;

	temp = NULL;
	if (line && *line)
		free(*line);
	*line = NULL;
	if (list && start && *start && *list == *start)
		*start = (*start)->next;
	if (list && *list && (*list)->prev)
		(*list)->prev->next = (*list)->next;
	if (list && *list && (*list)->next)
		(*list)->next->prev = (*list)->prev;
	if (list && *list)
		free(*list);
	if (list)
		*list = NULL;
}

t_bufflist	*get_dat_list(const int fd, t_bufflist **list)
{
	t_bufflist	*lst;

	if (list && *list == NULL)
		if ((*list = (t_bufflist*)malloc(sizeof(t_bufflist))))
		{
			(*list)->fd = fd;
			(*list)->next = NULL;
			(*list)->prev = NULL;
			ft_bzero((*list)->buff, BUFF_SIZE);
		}
	lst = *list;
	while (list && lst && lst->fd != fd)
	{
		if (lst->next == NULL && lst->fd != fd)
			if ((lst->next = (t_bufflist*)malloc(sizeof(t_bufflist))))
			{
				lst->next->fd = fd;
				lst->next->next = NULL;
				lst->next->prev = lst;
				ft_bzero(lst->next->buff, BUFF_SIZE);
			}
		lst = lst->next;
	}
	return (lst);
}

int			get_next_line(const int fd, char **line)
{
	size_t				linelen;
	static t_bufflist	*bufflist;
	int					res;
	t_bufflist			*lst;

	if (!line)
		return (-1);
	linelen = 0;
	res = 1;
	*line = NULL;
	lst = get_dat_list(fd, &bufflist);
	while (lst && !(res = get_buff(lst, line, &linelen)))
		if ((res = read(fd, lst->buff, BUFF_SIZE)) < 0 || !line ||
				(res == 0 && *(lst->buff) == '\0' && !(**line)))
			delelem(&lst, &bufflist, line);
	if (lst && *(lst->buff) == '\n')
	{
		ft_memcpy(lst->buff, (lst->buff) + 1, BUFF_SIZE - 1);
		lst->buff[BUFF_SIZE - 1] = '\0';
	}
	return (res);
}
