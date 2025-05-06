/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:42:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/11 13:42:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void foo_util(t_minishell *minishell, char *matrix_pos, char *redir_type)
{
	if (ft_strncmp(matrix_pos, ">>", 2) == 0)
		minishell->redirection = REDIR_APPEND;
	if (ft_strncmp(matrix_pos, "<<", 2) == 0)
		minishell->redirection = REDIR_HEREDOC;

	if (ft_strcmp(redir_type, "<<") == 0)
		minishell->prev_redir = REDIR_HEREDOC;
	else
		minishell->prev_redir = REDIR_IN;
}

static void	foo(t_minishell *minishell, char **matrix, int *current_pos,
    char *redir_type)
{
    (*current_pos)++;
    while (matrix[*current_pos])
    {
        if (!is_redirection(matrix[*current_pos], 0))
        {
            (*current_pos)++;
            continue;
		}
        if (ft_strncmp(matrix[*current_pos], redir_type, ft_strlen(redir_type)) == 0)
            (*current_pos)++;
        else
        {
			foo_util(minishell, matrix[*current_pos], redir_type);
            return;
        }
    }
    minishell->return_flag = true;
    (*current_pos)--;
    return;
}

/* static void	foo(t_minishell *minishell, char **matrix, int *current_pos)
{
    (*current_pos)++;
    while (matrix[*current_pos])
    {
        if (!is_redirection(matrix[*current_pos], 0))
        {
		    (*current_pos)++;
			continue ;
		}
        if (matrix[*current_pos][0] == REDIR_IN)
			(*current_pos)++;
		else if(matrix[*current_pos][0] != REDIR_IN)
		{
			minishell->redirection = matrix[*current_pos][0];
			minishell->prev_redir = REDIR_IN;
			return ;
		}
    }
	minishell->return_flag = true;
	(*current_pos)--;
    return ;
} */

static void	set_parent_input(t_minishell *minishell)
{
	t_pipe	pipe;

	if (minishell->pipe_tools.redir_count <= 0)
		return ;
	pipe = minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1];
	if (minishell->redirection != REDIR_IN)
		close(pipe.write_pipe);
	if (minishell->redirection != REDIR_IN && minishell->redirection != REDIR_HEREDOC)
		fd_redirection(STDIN_FILENO, pipe.read_pipe);
	//close(pipe.read_pipe); No cerrar el pipe de lectura aquí, ya que se necesita para leer el contenido
	//del pipe en el proceso padre.
}

static bool	is_child_process(t_minishell *minishell, pid_t child)
{
	if (child == 0)
	{
		minishell->pid = CHILD;
		return (true);
	}
	return (false);
}

static bool	process_child_cmd(t_minishell *minishell, char **matrix,
	int *operator_pos, int *current_pos)
{
	pid_t	child;

	if (minishell->redirection == REDIR_IN)
		foo(minishell, matrix, current_pos, "<");
	else if (minishell->redirection == REDIR_HEREDOC)
		foo(minishell, matrix, current_pos, "<<");
	if (minishell->return_flag)
		return (false);
	else
	{
		child = fork();
		if (is_child_process(minishell, child))
		{
			minishell->input_matrix = matrix_from_matrix(matrix, *operator_pos,
					*current_pos);
			return (true);
		}
		else
		{
			close(minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count
				- 1].write_pipe);
			waitpid(child, &minishell->exit_status, 0);
			if (WIFEXITED(minishell->exit_status))
				minishell->exit_status = WEXITSTATUS(minishell->exit_status);
		}
		*operator_pos = *current_pos + 1;
	}
	return (false);
}

void	handle_redir(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;
 
	i = 0;
	operator_pos = 0;
	// HAY HEREDOC EN MI MINISHELL->USER_INPUT?
		// MINISHELL->HEREDOC.EXIST = TRUE;
	matrix = split_input(minishell);
	// IF MINISHELL->HEREDOC.EXIST
		//TRATAMOS EL HEREDOC
	while (matrix[i]) // AQUI LLEGA LIMPIO SIN HEREDOC
	{
		if (is_redirection(matrix[i], 0)) // if (ft_strchr(matrix[i], '|'))
		{
			add_redir(minishell);
			set_redir_type(minishell, matrix[i]);
			if (process_child_cmd(minishell, matrix, &operator_pos, &i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
	set_parent_input(minishell);
	minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
			matrix_len(matrix));
	free_matrix(matrix);
}
// APUNTES PARA HEREDOC:

bool    ft_test(char *source, char *wanted) // para buscar "<<" en un str
{
	int i;
	int j;

	i = 0;
	while (source[i])
	{
		j = 0;
		while (wanted[j]
            && source[i + j]
            && source[i + j] == wanted[j])
			j++;
		if (!wanted[j])
			return true;
		i++;
	}
	return false;
}

typedef struct s_heredoc
{
	bool	exist; // si existe
	int		heredoc_num; // cuantos encuentra
	int		*heredoc_fds; // array de fd's con el contenido de cada bloque
	char	**delimits; // delimitadores de cada heredoc si la idea es eliminarlos desde el principio
}	heredoc_tools;

// wc << EOF1 << EOF2 | ls | wc << EOF3
// heredoc_num = 2 -> readline se ejecuta 2 veces
// fd_num = 1
// temp_fd -> se reserva con [fd_num] espacios

/* "INIT_HEREDOC_STRUCT" -> Cambiarle el nombre
while en cada pos de la matrix
si encuentro un heredoc, heredoc_num++;
el siguiente indice al heredoc, es el delimit de ese heredoc, se guarda en la matrix delimits.
si despues del heredoc la siguiente redireccion es diferente a heredoc, fd_num++;
se repite hasta terminar de parsearlo
---
IF (LA REDIRECCION DESPUES DEL HEREDOC ES DIFERENTE A HEREDOC)
	 "heredoc_fds_append"
	 PEDIR READLINE GUARDANDO EL CONTENIDO EN POSICION DE [i]

matrix_substract debe hacerse en la posicion de heredoc y su siguiente
---
Continua handle_redir normal


// Planteamiento en bloques:

// PLANTEAMIENTO DE HEREDOC QUE NO ME SIRVE
if (la siguiente redireccion es heredoc)
	char *line = readline("> ");
	if (!line)
		perror(mensaje de error, se sale con CTRL + D);
		se sale
	if (ft_strcmp(line, delimit[i]) == 0)
		free
		se sale
	free(line);

	
// PLANTEAMIENTO DE HEREDOC QUE SI ME SIRVE
if (la siguiente redireccion es dif a heredoc o NULL) -> me sirve
	char *line = readline("> ");
	if (!line)
		perror(mensaje de error, se sale con CTRL + D);
		se sale
	if (ft_strcmp(line, delimit[i]) == 0)
		free
		se sale
	ft_putendl_fd(line, heredoc_fd[j]);
	free(line);




// Planteamiento de una:

	if (matrix[i] == HEREDOC)
	{
		char *superline;
		char *line = readline("> ");
		while(line || strcmpy(EOF))
		{
			superline = join(superline, line);
			free(line);
			line = readline();
		}

		if (next_not_heardoc)
			ft_putendl_fd(superline, fd);
		else
			free(superline);
	}
*/
