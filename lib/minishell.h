#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Borrar, test para strcmp, hay que usar ft_strcmp

void	execute(char *cmd);
void	cmd_path(char **path_split, char *cmd);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
bool	is_valid(char *cmd_path);
bool	check_cmd(char **path_split);
char	*cmdcat(char *path, char *cmd);

#endif