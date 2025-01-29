#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Borrar, test para strcmp, hay que usar ft_strcmp

void	foo(void);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*cmdcat(char *path, char *cmd);

#endif