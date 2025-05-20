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
#include <fcntl.h>

/* --------------------- ENUMS -----------------------------*/

typedef enum e_error
{
	CMD_NOT_FOUND = 127,
} e_error;

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
}	e_built_in;

typedef enum e_process
{
	CHILD,
	PARENT
}	e_process;

/* -------------------------- STRUCTS ----------------------------*/

typedef struct s_quote
{
	char	type;
	bool	closed;
}	t_quote;

typedef struct s_pipe_tools
{
    t_pipe      *pipes;
    int         redir_count;
    int         STDIN;
    int         STDOUT;
}   t_pipe_tools;

typedef struct s_heredoc
{
	char	**delimits;
	int		delimit_index;
}	heredoc_tools;

typedef struct s_minishell
{
	char			*env_home;
	char			**envp;
	char			**declare_matrix;
	char			*shell_prompt;
	char			*user;
	char			*user_input;
	char			**input_matrix;
	char			**quoted_matrix;
	int				first_cmd;
	char			*cmd_path;
	int				args_num;
	bool			redir_existence;
	e_built_in		built_in_type;
	e_process		pid;
	t_pipe_tools	pipe_tools;
	int				exit_status;
	//another_test.c
	int				last_input;
	int				last_output;
	bool			invalid_input;
	heredoc_tools	heredoc;
}	t_minishell;


/*-------------------------  SRC ------------------------*/


/* MINISHELL_UTILS.C------------*/
void	init_minishell(t_minishell *minishell, char **envp);
char    *ft_getenv(char **envp, char *env_var);
void	free_minishell(t_minishell *minishell);

/* UPDATE_MINISHELL.C ----------*/
void	update_minishell(t_minishell *minishell, char **envp);


/*-----------------------  PARSE -----------------------*/


/* INPUT_UTILS.C ---------------*/
void	shell_prompt(t_minishell *minishell);
bool	valid_chr(char c);
bool	is_empty(t_minishell *minishell);
bool	is_empty_quotes(char *user_input);

/* INPUT.C ---------------------*/
bool	new_is_redirection(char *str);
bool 	is_quoted_redir_or_pipe(char *str);
char	**foo_split(t_minishell *minishell);
void	process_final_matrix(t_minishell *minishell);
void    get_input(t_minishell *minishell);
void 	parse_input(t_minishell *minishell);

/* PATH_UTILS.C ----------------*/
char	**concat_paths(char **splitted_path, char *cmd);
char	*cmdcat(char *path, char *cmd);
char 	*get_cmd_path(char **splitted_paths);

/* PATH.C ----------------------*/
char	**set_raw(char **envp);
char    *get_path(char **input_matrix, char **envp);

/* QUOTE_UTILS.C ---------------*/
void	quote_state(char current_char, t_quote *quote);
bool	check_quotes_balance(char *str);

/* SPLIT_UTILS.C ---------------*/
bool	init_vars(char ***matrix, char **word, t_quote *quote);
char	*str_append_char(char *word, char c);
char	*strtrim_and_free(char *str, char *c);
void	skip_middle_spaces(char *user_input, int *i);

/* SPLIT.C ----------------------*/
char	**split_input(t_minishell *minishell);
char	**process_character(char current_char, char **matrix, char **word, t_quote *quote);
char	**addmatrix(char **matrix, char **word);
char 	**finalize_parsing(char **matrix, char **word);

/* VAR_EXPANSION.C --------*/
void	set_expand_var(t_minishell *minishell);


/*------------------- BUILT-INS ---------------------*/


/* CD.C -------------------------*/
void	ft_cd(t_minishell *minishell);
/* ECHO.C -----------------------*/
void	ft_echo(t_minishell *minishell);
/* ENV.C ------------------------*/
void	ft_env(t_minishell *minishell);
/* EXIT.C -----------------------*/
void	ft_exit(t_minishell *minishell);
/* EXPORT.C ---------------------*/
void	ft_export(t_minishell *minishell);
/* PWD.C ------------------------*/
void	ft_pwd(void);
/* UNSET.C ----------------------*/
void	ft_unset(t_minishell *minishell);

/* BUILT-INS.C ----------------- */
bool	is_built_in(t_minishell *minishell);
void	exec_built_in(t_minishell *minishell);


/*------------------- REDIRECTIONS ---------------------*/


/*FT_PIPE.C --------------------*/
void	set_pipe_mode(int mode, t_pipe pipe);
void	ft_pipe(t_minishell *minishell);

/* FT_REDIR_IN.C ---------------*/
char	**clean_matrix_redirs(t_minishell *minishell);

/* REDIRECTIONS_UTILS.C --------*/
bool	check_valid_redir(t_minishell *minishell);
bool	check_redir_existence(t_minishell *minishell);
void	add_redir(t_minishell *minishell); // nombre rarete


/*--------------- PIPES_AND_REDIRECTION -----------------*/


/* EXPAND_REDIR.C --------------*/
bool	is_redirection(char *str, int pos); // es para la pos especifica
char 	*expand_pipe(t_minishell *minishell);

/* PIPE_UTILS.C ----------------*/
bool	cmd_not_found(t_minishell *minishell);
void	pipe_to_file(int read_from, int write_into);
void	redir_first_cmd(t_minishell *minishell);
void	fd_redirection(int from, int to);
void	store_fd(t_minishell *minishell);
void	reset_fd(t_minishell *minishell);
void	pipe_append(t_minishell *minishell, t_pipe *pipe);

/* FORK_REDIR.C ----------------*/
void	handle_redir(t_minishell *minishell);
bool    ft_test(char *source, char *wanted);

/* PIPE_LIBFT.C ----------------*/
t_pipe	create_pipe(void);

/* EXEC.C ----------------------*/
void	execute(t_minishell *minishell);
void	fork_exec(t_minishell *minishell);
bool	is_built_in(t_minishell *minishell);
void	exec_built_in(t_minishell *minishell);
void 	exec(t_minishell *minishell);


/*-------------------- VALIDATIONS ----------------------*/


/* VALID_CMD.C ---------------*/
bool	valid_cmd(char *cmd_path);
/* VALID_ENV_CHAR.C ----------*/
bool	valid_env_char(char c);
/* VALID_RL_INPUT.C ----------*/
bool	valid_rl_input(t_minishell *minishell);
/* VALID_SYMBOLS.C -----------*/
bool	valid_symbols(char *str);


/*----------------- SUELTOS EN SRC ------------ */


/* ANOTHER_TEST.C-------------*/

void redirect(t_minishell *minishell);

/* EXEC.C---------------------*/

void	execute(t_minishell *minishell);
void	exec(t_minishell *minishell);
void	fork_exec(t_minishell *minishell);

/* SIGNALS.C -----------------*/

void	setup_signals(void);
void 	handle_sign(int sign);

#endif
