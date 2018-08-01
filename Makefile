# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:19:19 by bcherkas          #+#    #+#              #
#    Updated: 2018/03/02 18:24:29 by bcherkas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
CC=clang
CFLAGS=-Wall -Wextra -Werror
GNLFILES=get_next_line.c
PRINTFFILES=ft_printf.c ft_vprintf.c printf_core.c checkflags.c s_parse.c ft_utoa_base.c d_parse.c getsigned.c writeformatted.c x_parse.c o_parse.c u_parse.c p_parse.c unicode_c.c width.c k_parse.c
FILES=ft_isdigit.c ft_memalloc.c ft_putnbr.c ft_striter.c ft_strnstr.c ft_isprint.c ft_memccpy.c ft_putnbr_fd.c ft_striteri.c ft_strrchr.c ft_isspace.c ft_memchr.c ft_putstr.c ft_strjoin.c ft_strrev.c ft_itoa.c ft_memcmp.c ft_putstr_fd.c ft_strlcat.c ft_strsplit.c ft_lstadd.c ft_memcpy.c ft_strcat.c ft_strlen.c ft_strstr.c ft_abs.c ft_lstdel.c ft_memdel.c ft_strchr.c ft_strmap.c ft_strsub.c ft_atoi.c ft_lstdelone.c ft_memmove.c ft_strclr.c ft_strmapi.c ft_strtrim.c ft_bzero.c ft_lstiter.c ft_memset.c ft_strcmp.c ft_strncat.c ft_tolower.c ft_intlen.c ft_lstlen.c ft_putchar.c ft_strcpy.c ft_strncmp.c ft_toupper.c ft_isalnum.c ft_lstmap.c ft_putchar_fd.c ft_strdel.c ft_strncpy.c ft_isalpha.c ft_lstnew.c ft_putendl.c ft_strdup.c ft_strnequ.c ft_isascii.c ft_putendl_fd.c ft_strequ.c ft_strnew.c ft_lstdelcontent.c ft_lstpushback.c ft_delarr.c ft_strsplit_lst.c $(PRINTFFILES) $(GNLFILES)
OBJ=$(FILES:.c=.o)
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
