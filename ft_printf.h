/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:19:30 by bcherkas          #+#    #+#             */
/*   Updated: 2018/03/02 19:06:50 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define MAXFORMATID 10
# define COLORSMAX 11

typedef struct		s_pf
{
	size_t			sharp;
	size_t			null;
	size_t			min;
	size_t			plus;
	size_t			space;
	size_t			width;
	size_t			prec;
	size_t			comma;
	int				lenmode;
	int				extra;
}					t_pf;

typedef struct		s_func
{
	char			flag;
	struct s_buf	*(*func)(va_list ap, struct s_pf *fm,
		struct s_buf *temp, char format);
}					t_func;

typedef struct		s_buf
{
	size_t			bufflen;
	size_t			size;
	char			*buff;
	struct s_buf	*next;
	struct s_buf	*firstelem;
}					t_buf;

char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_atoi(const char *str);
char				*ft_strnew(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);

int					printf_core(char *strg, t_buf **buflst,
					va_list ap, va_list start);
int					ft_printf(const char *format, ...);
int					ft_asprintf(char **str, const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_snprintf(char *str, size_t size,
					const char *format, ...);
int					ft_vasprintf(char **str,
					const char *format, va_list ap);
int					ft_vdprintf(int fd,
					const char *format, va_list ap);
int					ft_vprintf(const char *format, va_list ap);
int					ft_vsnprintf(char *str, size_t size,
					const char *format, va_list ap);

void				checkflags(char **str, t_pf *format);
int					lastpreparations(char **str, t_pf *format);
void				changeposition(char **str, va_list ap, va_list start);
void				width(char **str, t_pf *format, va_list ap, va_list start);
void				getlength(char **str, t_pf *format);

size_t				getsigned(va_list ap, int intlen, int *min);
size_t				getunsigned(va_list ap, int intlen);
char				*ft_utoa_base(size_t n, int base, int big);
void				ft_itoa_base(size_t n, int base, char *fin, t_pf *fm);
size_t				base_ulen(size_t n, int base, size_t sep);
void				unicode_c(unsigned v, size_t size,
					uint8_t *buff, size_t *len);
uint8_t				*unicode_s(wint_t *v, t_pf *fm);
t_buf				*null_pointer(t_pf *fm, t_buf *temp);

int					writeformatted(char *buff, size_t size, t_buf **buflst);
int					writestr(char **str, char *save, t_buf **buflst, size_t *i);
int					printbuff(t_buf *buflst, int fd);
int					printtostring(t_buf *buflst, char *str, size_t max);
int					allocstring(t_buf *buflst, char **str);
int					saveexit(t_buf *delit, va_list ap, va_list start);
int					n_parse(va_list ap, t_buf *bst, char **str);

t_buf				*s_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*c_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*d_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*o_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*u_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*x_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*p_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*b_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*k_parse(va_list ap, t_pf *fm, t_buf *temp, char format);
t_buf				*r_parse(va_list ap, t_pf *fm, t_buf *temp, char format);

#endif
