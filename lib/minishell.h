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
#include <stdbool.h>

typedef struct s_input
{
	char	*user_input;
	char	**input_matrix;
}	t_input;

void	execute(t_input *input, char **envp);
void	concat_paths(char **path_split, char *cmd);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
bool	not_found(char *filepath, char **input_matrix);
bool	is_valid(char *cmd_path);
char 	*get_cmd_path(char **splitted_paths, char **cmd_path);
char	*cmdcat(char *path, char *cmd);
void	fork_exec(char *cmd_path, char **cmd, char **envp);
char    *get_path(char **input_matrix, char **envp);
char	**set_raw(char **envp);
char    *ft_getenv(char **envp, char *env_var);
bool	valid_input(char *input);
void    get_input(t_input *input);
void	free_input(t_input *input);

#endif