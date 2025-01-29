/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:22:19 by antonimo          #+#    #+#             */
/*   Updated: 2024/11/28 11:15:02 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

# define BUFFER_SIZE 2

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *ptr, int value, size_t n);
void	ft_bzero(void *ptr, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int chr);
char	*ft_strrchr(const char *str, int chr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// LIBFT - LINKED LIST
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// CHAR UTILITIES
int		count_char_in_str(char *str, char c);
bool	all_chars_same(char *str, char c);
bool	check_strchr_gnl(char *str, char chr);

// ERROR
void	error_msg(char *msg);

// GNL - GNL UTILITIES
char	*get_next_line(int fd);
char	*ft_line_remaining(char *stat_buff);
char	*ft_line(char *stat_buff);
char	*ft_read_buffersize(int fd, char *stat_buff);
int		ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *str, char chr);
void	*ft_calloc_gnl(size_t size, size_t type);

// MATRIX UTILITIES
char	**create_matrix(int n);
void	free_matrix(char **matrix);
int		matrixlen(char **matrix);
void	print_matrix(char **matrix);

typedef struct s_pipe
{
	int	read_pipe;
	int	write_pipe;
}	t_pipe;

#endif