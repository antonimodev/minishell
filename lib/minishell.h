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

typedef enum e_redirection // ls >> grep
{
    NONE,           // No es un operador
    PIPE,           // |
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // <<
}	e_redirection;

typedef enum e_process
{
	CHILD,
	PARENT
}	e_process;

/*typedef	struct s_prompt
{
	char	*user;
	char	*arrow;
	char	*pwd; // ft_pwd que habra que modificar
	char	*prompt;
}	t_prompt;*/

typedef struct s_quote
{
	char	type;
	bool	closed;
}	t_quote;

/*typedef struct s_pipe
{
	int	read_pipe;
	int	write_pipe;
}	t_pipe;*/

// Add to your t_pipe_tools struct in minishell.h
typedef struct s_pipe_tools
{
    t_pipe      *pipes;
    int         redir_count; 
    int         total_cmds;   // Total commands in pipeline
    int         cmd_position; // Current command position (1-indexed)
    int         STDIN;
    int         STDOUT;
}   t_pipe_tools;

typedef struct s_minishell
{
	char			**envp;
	int				exit_status;
	char			*user;
	char			*shell_prompt;
	char			*last_prompt;
	char			*user_input;
	char			**input_matrix;
	char			*cmd_path;
	int				args_num;
	bool			redir_existence;
	e_redirection	redirection;
	e_built_in		built_in_type;
	e_process		pid;
	t_pipe_tools	pipe_tools;
}	t_minishell;


void	print_minishell(t_minishell *minishell);

/*-------------------------  SRC ------------------------*/

/* QUOTE_UTILS.C ---------------*/
void	quote_state(char current_char, t_quote *quote);
bool	check_quotes_balance(char *str);

/* MINISHELL_UTILS.C------------*/
void	init_minishell(t_minishell *minishell, char **envp);
char    *ft_getenv(char **envp, char *env_var);
void	free_minishell(t_minishell *minishell);

/* UPDATE_MINISHELL.C ----------*/
void	update_minishell(t_minishell *minishell, char **envp);


/*-----------------------  PARSE -----------------------*/

/* INPUT.C ---------------------*/
void    get_input(t_minishell *minishell);
void 	parse_input(t_minishell *minishell);

/* INPUT_UTILS.C -----------------*/
void	shell_prompt(t_minishell *minishell);
bool	valid_chr(char c);
bool	is_empty(t_minishell *minishell);

/* SPLIT.C ----------------------*/
char	**split_input(t_minishell *minishell);
char	**process_character(char current_char, char **matrix, char **word, t_quote *quote);
char	**addmatrix(char **matrix, char **word);
char 	**finalize_parsing(char **matrix, char **word);

/* SPLIT_UTILS.C -------------------*/
bool	init_vars(char ***matrix, char **word, t_quote *quote);
char	*str_append_char(char *word, char c);
char	*strtrim_and_free(char *str, char *c);
void	skip_middle_spaces(char *user_input, int *i);

/*------------------- BUILT-INS -------------------------*/

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
/* PWD.C -----------------------*/
void	ft_pwd();
/* UNSET.C ----------------------*/
void	ft_unset(t_minishell *minishell);


/*------------------- VARIABLE_EXPANSION.C -------------------------*/
void	set_expand_var(t_minishell *minishell);

/* REDIRECTIONS_UTILS.C --------*/
bool	check_valid_redir(t_minishell *minishell);
bool	check_redir_existence(t_minishell *minishell);
void	set_redir_type(t_minishell *minishell, char *str);
void	add_redir(t_minishell *minishell); // nombre rarete

/* EXEC.C ----------------------*/
void	execute(t_minishell *minishell);
void	fork_exec(t_minishell *minishell);
bool	is_built_in(t_minishell *minishell);
void	exec_built_in(t_minishell *minishell);
void 	exec(t_minishell *minishell);

/* PATH_UTILS.C ----------------*/
char	**concat_paths(char **splitted_path, char *cmd);
char	*cmdcat(char *path, char *cmd);
char 	*get_cmd_path(char **splitted_paths);

/* PATH.C ----------------------*/
char	**set_raw(char **envp);
char    *get_path(char **input_matrix, char **envp);


/*-------------------- VALIDATIONS ----------------------*/
bool	valid_cmd(char *cmd_path);
bool	valid_symbols(char *str);
bool	valid_rl_input(t_minishell *minishell);
bool	valid_env_char(char c);

/* SIGNALS.C -------------------*/
void	setup_signals(void);
void 	handle_sign(int sign);

/*--------------- PIPES_AND_REDIRECTION -----------------*/

/* EXPAND_REDIR.C --------------*/
void	set_redirections(t_minishell *minishell);
bool	is_redirection(char *str, int pos);
char 	*expand_pipe(t_minishell *minishell);

/* PIPE_UTILS.C ----------------*/
void	fd_redirection(int from, int to);
void	redirect(t_minishell *minishell);
void	store_fd(t_minishell *minishell);
void	reset_fd(t_minishell *minishell);
void	pipe_append(t_minishell *minishell, t_pipe *pipe);

// CREATE PIPE
t_pipe	create_pipe(void);

/*---------------- REDIRECTIONS --------------------*/
void	ft_pipe(t_minishell *minishell);
void	ft_redir_in(t_minishell *minishell);
void	ft_redir_out(t_minishell *minishell);
void	ft_redir_append(t_minishell *minishell);
void	ft_redir_heredoc(t_minishell *minishell);


#endif
