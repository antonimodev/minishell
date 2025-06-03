/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:11:40 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/03 15:38:15 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --------------------- DEFINES ---------------------------*/
# define _POSIX_C_SOURCE 199309L

/* --------------------- COLORS ----------------------------*/
# define BOLD_GREEN "\033[1;32m"
# define BOLD_TURQUOISE "\033[1;36m"
# define BOLD_YELLOW "\033[1;33m"
# define RESET "\033[0m"

/* --------------------- INCLUDES --------------------------*/
# include "libft.h"
# include "matrix_utils.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>

/* ------------------------ GLOBAL -------------------------*/

extern int		g_signal;

/* --------------------- ENUMS -----------------------------*/

typedef enum t_error
{
	CMD_NOT_FOUND = 127,
}	t_error;

typedef enum t_built_in
{
	FT_NULL,
	FT_ECHO,
	FT_CD,
	FT_PWD,
	FT_EXPORT,
	FT_UNSET,
	FT_ENV,
	FT_EXIT
}	t_built_in;

typedef enum t_process
{
	CHILD,
	PARENT
}	t_process;

/* -------------------------- STRUCTS ----------------------------*/

typedef struct s_quote
{
	char	type;
	bool	closed;
}	t_quote;

typedef struct s_fd_tools
{
	t_pipe	*pipes;
	int		stdin;
	int		stdout;
}	t_fd;

typedef struct s_heredoc
{
	char	**delimits;
	int		delimit_index;
}	t_heredoc;

typedef struct s_redir
{
	bool	redir_exist;
	bool	invalid_input;
	int		redir_count;
	int		last_input;
	int		last_output;
}	t_redir;

typedef struct s_minishell
{
	char			*user_input;
	char			*user;
	char			*shell_prompt;
	char			*last_prompt;
	char			**envp;
	char			**declare_matrix;
	char			*env_home;
	char			**input_matrix;
	char			**quoted_matrix;
	char			*cmd_path;
	int				args_num;
	int				first_cmd;
	t_built_in		built_in_type;
	t_process		pid;
	t_fd			fd_tools;
	t_redir			redir;
	t_heredoc		heredoc;
	int				exit_status;
}	t_minishell;

/*-------------------------  MAIN ------------------------*/

/* MINISHELL_UTILS.C ------------*/
void	init_minishell(t_minishell *minishell, char **envp);
char	*ft_getenv(char **envp, char *env_var);
void	free_minishell(t_minishell *minishell);
void	increment_shlvl(t_minishell *minishell);
void	default_env(char ***system_envp);

/* UPDATE_MINISHELL.C -----------*/
void	update_minishell(t_minishell *minishell, char **envp);

/*-----------------------  PARSE -----------------------*/

/* INPUT.C ----------------------*/
void	get_input(t_minishell *minishell);
void	parse_input(t_minishell *minishell);

/* INPUT_UTILS.C ----------------*/
bool	valid_chr(char c);
bool	is_empty(t_minishell *minishell);
bool	is_empty_quotes(char *user_input);
bool	str_equal(char *source, char *wanted);

/* PROMPT.C ---------------------*/
void	shell_prompt(t_minishell *minishell);

/* IS_REDIRECTION.C -------------*/
bool	is_redirection(char *str);
bool	is_quoted_redir_or_pipe(char *str);

/* PATH.C -----------------------*/
char	**set_raw(char **envp);
char	*get_path(char **input_matrix, char **envp);

/* PATH_UTILS.C -----------------*/
char	**concat_paths(char **splitted_path, char *cmd);
char	*cmdcat(char *path, char *cmd);
char	*get_cmd_path(char **splitted_paths);

/* QUOTE_UTILS.C ----------------*/
void	quote_state(char current_char, t_quote *quote);
bool	check_quotes_balance(char *str);

/* SPLIT.C ----------------------*/
char	**split_with_quotes(t_minishell *minishell);
char	**split_without_quotes(t_minishell *minishell);
char	**process_character(char current_char, char **matrix, char **word,
			t_quote *quote);
char	**addmatrix(char **matrix, char **word);
char	**finalize_parsing(char **matrix, char **word);

/* SPLIT_UTILS.C ----------------*/
bool	init_vars(char ***matrix, char **word, t_quote *quote);
char	*str_append_char(char *word, char c);
char	*strtrim_and_free(char *str, char *c);
void	skip_middle_spaces(char *user_input, int *i);
void	process_final_matrix(t_minishell *minishell);

/* VAR_EXPANSION.C --------------*/
void	set_expand_var(t_minishell *minishell);

/*------------------- BUILT-INS ---------------------*/

/* BUILT-INS.C ------------------*/
bool	is_built_in(t_minishell *minishell);
void	exec_built_in(t_minishell *minishell);

/* ECHO.C -----------------------*/
void	ft_echo(t_minishell *minishell);

/* CD.C -------------------------*/
void	ft_cd(t_minishell *minishell);

/* CD_UTILS.C -------------------*/
bool	find_in_matrix(char **matrix, char *var_name, int *index);
void	set_env(t_minishell *minishell, char *env_var, char *value);
void	update_pwd(t_minishell *minishell, char *old_pwd);
bool	cd_access_error(t_minishell *minishell, char *path);
void	cd_error(t_minishell *minishell, char *path);

/* PWD.C ------------------------*/
void	ft_pwd(void);

/* EXPORT.C ---------------------*/
void	ft_export(t_minishell *minishell);

/* EXPORT_CASES.C ---------------*/
void	export_no_equal(t_minishell *minishell, char *arg);
char	**export_equal(char **matrix, char *arg, char *var_name);
char	**export_plus_equal(char **matrix, char *arg, char *var_name);

/* EXPORT_DECLARE.C -------------*/
void	show_declare_matrix(char **declare_matrix);

/* EXPORT_UTILS.C ---------------*/
int		get_chr_index(char *str, char chr);
char	*ft_strjoin_at(const char *s1, const char *s2, size_t pos);
char	*get_envp_var_name(char *env_var);
char	*clean_chr_from_str(char *str, char chr);

/* UNSET.C ----------------------*/
void	ft_unset(t_minishell *minishell);

/* ENV.C ------------------------*/
void	ft_env(t_minishell *minishell);

/* EXIT.C -----------------------*/
void	ft_exit(t_minishell *minishell);

/*------------------- EXECUTION ---------------------*/

/* EXEC.C -----------------------*/
void	execute(t_minishell *minishell);
void	exec(t_minishell *minishell);
void	fork_exec(t_minishell *minishell);
void	get_exit_status(t_minishell *minishell, pid_t pid);

/*------------------- REDIRECTIONS ---------------------*/

/* REDIRECT.C -------------------*/
void	redirect(t_minishell *minishell);

/* REDIRECT_UTILS.C -------------*/
bool	check_heredoc_presence(t_minishell *minishell);
void	handle_parent_pipe(t_minishell *minishell, bool has_heredoc);
void	handle_child_pipe(t_minishell *minishell, bool has_heredoc);

/* REDIR_IN.C -------------------*/
void	heredoc_handle_sign(int sign);
void	setup_heredoc_signs(void);
void	redir_in(t_minishell *minishell, int index);
void	redir_heredoc(t_minishell *minishell, int index);

/* REDIR_IN_UTILS.C -------------*/
bool	is_delimiter(t_minishell *minishell, char *line);
void	handle_heredoc_eof(t_minishell *minishell);
void	handle_heredoc_sigint(t_minishell *minishell, t_pipe *temp_pipe);
bool	check_eof_or_delimiter(t_minishell *minishell, char *line);
int		heredoc_loop(t_minishell *minishell, int last_fd, t_pipe temp_pipe);

/* REDIR_OUT.C ------------------*/
void	redir_out(t_minishell *minishell, int index);
void	redir_append(t_minishell *minishell, int index);

/* REDIR_PIPE.C -----------------*/
void	close_all_read_pipes(t_minishell *minishell);
void	close_unused_pipes(t_minishell *minishell);
void	close_read_pipes(t_minishell *minishell);
void	close_write_pipes(t_minishell *minishell);
void	ft_pipe(t_minishell *minishell);

/* REDIR_CMD_CLEANER.C ----------*/
void	clean_matrix_redirs(t_minishell *minishell);

/* REDIRECTIONS_UTILS.C ---------*/
bool	check_valid_redir(t_minishell *minishell);
bool	check_redir_existence(t_minishell *minishell);
void	minishell_add_redir(t_minishell *minishell);

/*--------------- PIPES_AND_REDIRECTION -----------------*/

/* EXPAND_REDIR.C ---------------*/
bool	redir_at_pos(char *str, int pos);
char	*expand_pipe(t_minishell *minishell);

/* PIPE_UTILS.C -----------------*/
void	redir_first_cmd(t_minishell *minishell);
void	minishell_pipe_append(t_minishell *minishell, t_pipe *pipe);

/* FORK_REDIR.C -----------------*/
void	handle_redir(t_minishell *minishell);

/* FORK_REDIR_UTILS.C -----------*/
bool	is_child_process(t_minishell *minishell, pid_t child);
bool	process_child_cmd(t_minishell *minishell, char **matrix,
			int *operator_pos, int *current_pos);

/* PIPE_LIBFT.C -----------------*/
t_pipe	create_pipe(void);

/*-------------------- VALIDATIONS ----------------------*/

/* VALID_CMD.C ------------------*/
bool	valid_cmd(char *cmd_path);
bool	cmd_not_found(t_minishell *minishell);

/* VALID_REDIR.C ----------------*/
bool	check_redir_existence(t_minishell *minishell);
bool	check_valid_redir(t_minishell *minishell);

/* VALID_REDIR_UTILS.C ----------*/
bool	consecutive_redirs(t_minishell *minishell);
bool	pipe_after_redir(char **input_matrix, int index);

/* VALID_ENV_CHAR.C -------------*/
bool	valid_env_char(char c);

/* VALID_RL_INPUT.C -------------*/
bool	valid_rl_input(t_minishell *minishell);

/* VALID_SYMBOLS.C --------------*/
bool	valid_symbols(char *str);

/*----------------- UTILS --------------------*/

/* FD_UTILS.C -------------------*/
void	fd_redirection(int from, int to);
void	minishell_store_fd(t_minishell *minishell);
void	minishell_reset_fd(t_minishell *minishell);
void	write_from_fd(int read_from, int write_into);
void	set_fd_mode(int fd, t_pipe pipe);

/* SIGNALS.C --------------------*/
void	setup_signals(void);
void	set_std_signals(void);
void	set_parent_signals(void);

#endif