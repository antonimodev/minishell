#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

void	execute(char **cmd, char **envp);
void	cmd_path(char **path_split, char *cmd);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
bool	is_valid(char *cmd_path);
char 	*get_cmd(char **path_split);
char	*cmdcat(char *path, char *cmd);
void	fork_exec(char *cmd_path, char **cmd, char **envp);
char    *get_path(char **cmd, char **envp);
char    *get_env(char **envp, char *env_var);

#endif