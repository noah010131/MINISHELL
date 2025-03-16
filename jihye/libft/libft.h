/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeki2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:47:52 by jihyeki2          #+#    #+#             */
/*   Updated: 2024/09/19 18:19:59 by jihyeki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int num);
int		ft_atoi(const char *str);
void	*ft_bzero(void *ptr, size_t len);
void	*ft_calloc(size_t element_count, size_t element_size);
void	*ft_memchr(const void *ptr, int v, size_t num);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void	*ft_memset(void *ptr, int v, size_t c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *str, const char *sub, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dest, const void *sorce, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);

char	*read_line(int fd, char *next, char *buffer);
void	ft_strlcpy_gnl(char *new_s, char *line, int n_pos);
char	*next_line(char *line);
char	*get_next_line(int fd);
int		ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *buffer, char n);
void	*ft_memset_gnl(void *ptr, int v, size_t c);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*get_line_my(char *line);

int		ft_printf(const char *format, ...);
int		ft_format_check(const char *format, va_list ap);
int		ft_format_c(int c);
int		ft_format_s(char *s);
int		ft_format_di(long di);
int		ft_format_u(unsigned int u);
int		ft_format_x(unsigned long x, char *hexa);
int		ft_format_p(void *ptr);

#endif
