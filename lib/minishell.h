#ifndef MINISHELL_H
#define MINISHELL_H

/* --------------------- DEFINES ---------------------------*/
# define _POSIX_C_SOURCE 199309L
# define UNUSED(x) (void)(x)

/* --------------------- COLORS ----------------------------*/
# define BOLD_GREEN "\033[1;32m"
# define BOLD_TURQUOISE "\033[1;36m"
# define BOLD_YELLOW "\033[1;33m"
# define RESET "\033[0m"

/* --------------------- INCLUDES --------------------------*/
#include "libft.h"
#include "matrix_utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

/* --------------------- ENUMS -----------------------------*/
typedef enum e_built_in
{
	FT_NULL,
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT
} e_built_in;

typedef	struct s_prompt
{
	char	*user; // guardar el usuario (minishell->user)
	char	*arrow; // guardar la flecha con formato de color
	char	*pwd; // ft_pwd que habra que modificar
	char	*prompt; // res final
}	t_prompt;

typedef struct s_quote
{
	bool	closed;
	char	type;
}	t_quote;


typedef struct s_minishell
{
	char		**envp; // Añadir variable envp para exports
	char		*user;
	char		*user_input;
	char		**input_matrix;
	char		*cmd_path;
	int			args_num;
	t_prompt	shell_prompt;
	e_built_in	built_in_type;
}	t_minishell;


/*-------------------- MINISHELL -------------------------*/

/* --------------------- FORK.C ----------------------------*/
void	exec_cmd(t_minishell *minishell, char **envp);
void	fork_exec(t_minishell *minishell);

/* ------------------ PATH_UTILS.C -------------------------*/
void	execute(t_minishell *minishell);
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
char	*clean_input(t_minishell *minishell);
int		count_with_spaces(char  *user_input);
void 	parse_input(t_minishell *minishell);
bool	valid_input(char *input);
void	free_minishell(t_minishell *minishell);
bool	is_empty(t_minishell *minishell);
bool	no_skip(char c);
void	shell_prompt(t_minishell *minishell);

/**/
void	exec_built_in(t_minishell *minishell);
bool	is_built_in(t_minishell *minishell);

/*--------------------- BUILT_INS -------------------------*/
void	ft_pwd(t_minishell *minishell);
void    ft_echo(t_minishell *minishell);
void	ft_cd(t_minishell *minishell);
void	ft_export(t_minishell *minishell);
void	ft_exit(t_minishell *minishell);
bool	ft_isnumber(t_minishell *minishell);

/*--------------------- PARSE ----------------------------*/
char	**think_v2(t_minishell *minishell);

/* ---- TESTING ---- */
char	*custom_strtrim(char *str, char c);
void	skip_middle_spaces(char *user_input, int *i);

char	**matrix_substract(char **matrix, unsigned int index);
char    **matrix_cpy(char **src, int extra_slots);
char	**matrix_append(char **matrix, char *new_str);
void	ft_env(t_minishell *minishell);
void	set_envp(t_minishell *minishell, char **envp);
void	init_minishell(t_minishell *minishell, char **envp);
void	ft_unset(t_minishell *minishell);
bool	valid_symbols(char *str);
void	setup_signals(void);
void 	handle_sign(int sign);

#endif