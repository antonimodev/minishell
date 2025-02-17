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

/* --------------------- COLORS ----------------------------*/
# define BOLD_GREEN "\033[1;32m"
# define BOLD_TURQUOISE "\033[1;36m"
# define BOLD_YELLOW "\033[1;33m"
# define RESET "\033[0m"

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

/* typedef struct s_quotes{
	int			s_quotes;
	int			d_quotes;
	bool		valid_quotes;
}	t_quotes; */
typedef struct s_tokenizer
{
    char	**matrix;
    int		matrix_index;
}	t_tokenizer;

typedef struct s_token_state
{
    bool in_quotes; // flag para abierto/cerrado
    char current_quote; // guarda si es single o double
    int j; // iterador para word
    char *token; // word
	int	len;
} t_token_state;

typedef struct quote{
	bool	closed;
	char	type;
} t_quote;


typedef struct s_minishell
{
	char		**env; // Añadir variable envp para exports
	char		*user;
	char		*user_input;
	char		**input_matrix;
	char		*cmd_path;
	int			args_num;
	e_built_in	built_in_type;
}	t_minishell;
/*-------------------- MINISHELL -------------------------*/
char  **clean_split(t_tokenizer *split);
void	free_matrix_error(char **matrix, int i);

/* --------------------- FORK.C ----------------------------*/
void	exec_cmd(t_minishell *minishell, char **envp);
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
void    get_input(t_minishell *minishell, char **envp);
char	*clean_input(t_minishell *minishell);
int		count_with_spaces(char  *user_input);
void 	parse_input(t_minishell *minishell, char **envp);
bool	valid_input(char *input);
void	free_minishell(t_minishell *minishell);
bool	is_empty(t_minishell *minishell);
bool	no_skip(char c);
void	shell_prompt(t_minishell *minishell);

/**/
void	exec_built_in(t_minishell *minishell, char **envp);
bool	is_built_in(t_minishell *minishell);

/*--------------------- BUILT_IN.C -------------------------*/
void	ft_pwd(t_minishell *minishell);
void	ft_cd(t_minishell *minishell);
void	ft_export(t_minishell *minishell, char **envp);
void	ft_exit(t_minishell *minishell);
bool	ft_isnumber(t_minishell *minishell);

/*--------------------- TESTING_NEW_SPLIT.C ----------------------------*/
char	**think(t_minishell *minishell);
char	**think_v2(t_minishell *minishell);
char	**custom_split(char *user_input);
void	fill_tokens(char *user_input, t_tokenizer *split);
void	handle_quotes(char *str, int *i, t_token_state *state);
char	*build_token(char *user_input, int *i_pos);

/* ---- TESTING ---- */
char	*custom_strtrim(char *str, char c);
void	skip_middle_spaces(char *user_input, int *i);

#endif