# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 19:19:19 by bcherkas          #+#    #+#              #
#    Updated: 2018/11/22 18:01:38 by bcherkas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re MESSAGE
CC=clang
CFLAGS=-Wall -Wextra -Werror -I./includes

PRINTFDIR=ft_printf/
GNLDIR=getnextline/
CHARDIR=charlib/
DIGITDIR=digitlib/
LSTDIR=lstlib/
MEMDIR=memlib/
STRDIR=strlib/
TEXTDIR=textlib/
PIPEDIR=pipelib/

GNLLIB=get_next_line.c

PRINTFLIB=ft_printf.c ft_vprintf.c printf_core.c checkflags.c s_parse.c \
			ft_utoa_base.c d_parse.c getsigned.c writeformatted.c x_parse.c \
			o_parse.c u_parse.c p_parse.c unicode_c.c width.c k_parse.c

CHARLIB=ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_isspace.c ft_tolower.c ft_toupper.c

DIGITLIB=ft_abs.c ft_atoi.c ft_intlen.c ft_itoa.c ft_atof.c ft_ftoa.c

LSTLIB=ft_lstadd.c ft_lstdel.c ft_lstdelcontent.c ft_lstdelone.c ft_lstiter.c \
	   ft_lstlen.c ft_lstmap.c ft_lstnew.c ft_lstpushback.c ft_lstsort.c

MEMLIB=ft_bzero.c ft_delarr.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c

STRLIB=ft_strcat.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strlen.c \
	   ft_strncat.c ft_strnequ.c ft_strrchr.c ft_strsplit_lst.c ft_strtrim.c \
	   ft_strchr.c ft_strcpy.c ft_strequ.c ft_strjoin.c ft_strmap.c \
	   ft_strncmp.c ft_strnew.c ft_strrev.c ft_strstr.c ft_strclr.c \
	   ft_strdel.c ft_striter.c ft_strlcat.c ft_strmapi.c ft_strncpy.c \
	   ft_strnstr.c ft_strsplit.c ft_strsub.c

TEXTLIB=ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c

PIPELIB=ft_popen.c ft_pclose.c

FILES=$(addprefix $(PRINTFDIR), $(PRINTFLIB)) \
	  $(addprefix $(GNLDIR), $(GNLLIB)) \
	  $(addprefix $(CHARDIR), $(CHARLIB)) \
	  $(addprefix $(DIGITDIR), $(DIGITLIB)) \
	  $(addprefix $(LSTDIR), $(LSTLIB)) \
	  $(addprefix $(MEMDIR), $(MEMLIB)) \
	  $(addprefix $(STRDIR), $(STRLIB)) \
	  $(addprefix $(TEXTDIR), $(TEXTLIB)) \
	  $(addprefix $(PIPEDIR), $(PIPELIB))

OBJ=$(FILES:.c=.o)
NAME=libft.a

all: MESSAGE $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@echo "\nlibft compiled"

MESSAGE:
	@echo "Compiling libft"

%.o: %.c
	@printf "."
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@echo "libft cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "libft fcleaned"

re: fclean all
