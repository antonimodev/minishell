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

# define UNUSED(x) (void)(x)


typedef enum e_built_in
{
	FT_NULL,
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
} e_built_in;

typedef struct s_minishell
{
	char		*user_input;
	char		**input_matrix;
	char		*cmd_path;
	e_built_in	built_in_type;
}	t_minishell;
/*-------------------- MINISHELL -------------------------*/

/* --------------------- FORK.C ----------------------------*/
void	fork_exec(t_minishell *minishell, char **envp);

/* ------------------ PATH_UTILS.C -------------------------*/
void	execute(t_minishell *minishell, char **envp);
char	**concat_paths(char **splitted_path, char *cmd);
char	*cmdcat(char *path, char *cmd);
char 	*get_cmd_path(char **splitted_paths);
bool	is_valid(char *cmd_path);


/*---------------------- PATH.C ----------------------------*/
char	**set_raw(char **envp);
char    *get_path(char **input_matrix, char **envp);
char    *ft_getenv(char **envp, char *env_var);

/*--------------------- INPUT.C ----------------------------*/
void    get_input(t_minishell *minishell);
void 	parse_input(t_minishell *minishell, char **envp);
bool	valid_input(char *input);
void	free_minishell(t_minishell *minishell);

void	exec_built_in(t_minishell *minishell);
bool	is_built_in(t_minishell *minishell);
void	ft_pwd(t_minishell *minishell);

#endif