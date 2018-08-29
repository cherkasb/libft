/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 15:15:47 by bcherkas          #+#    #+#             */
/*   Updated: 2018/03/02 18:23:17 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct			s_bufflist
{
	int					fd;
	char				buff[BUFF_SIZE];
	struct s_bufflist	*next;
	struct s_bufflist	*prev;
}						t_bufflist;

void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncat(char *s1, const char *s2, size_t size);
char					*ft_strnew(size_t size);

int						get_next_line(const int fd, char **line);

#endif
