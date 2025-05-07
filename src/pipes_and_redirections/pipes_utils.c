/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:46:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/30 13:16:13 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_parent(t_minishell *minishell);
static void	redirect_child(t_minishell *minishell);

bool	cmd_not_found(t_minishell *minishell)
{
	if (!minishell->cmd_path)
	{
		printf("minishell: %s: command not found\n",
			minishell->input_matrix[0]);
		minishell->exit_status = CMD_NOT_FOUND;
		return (true);
	}
	return (false);
}

void	pipe_to_file(int read_from, int write_into)
{
	char	buffer;

	while (read(read_from, &buffer, 1) > 0)
	{
		if (write(write_into, &buffer, 1) != 1)
		{
			perror("Error al escribir en la salida estándar");
			break;
		}
	}
}

void	redir_first_cmd(t_minishell *minishell)
{
    int current_pipe;

	if (cmd_not_found(minishell))
		exit(CMD_NOT_FOUND);
    current_pipe = minishell->pipe_tools.redir_count - 1;
    set_pipe_mode(STDOUT_FILENO, minishell->pipe_tools.pipes[current_pipe]);
    return ;
}

void    redirect(t_minishell *minishell)
{
    if (minishell->pid == CHILD)
		redirect_child(minishell);
    else
        redirect_parent(minishell);	
}

static void	redirect_child(t_minishell *minishell) // caso chungo -> wc > output.txt > perro.txt << EOF1 << EOF2 << EOF3
{
	int	i;

	i = 0;
	if (minishell->first_cmd == 1)
		redir_first_cmd(minishell); // redirecciona STDOUT a Current_pipe
	else
		ft_pipe(minishell);
	while (minishell->input_matrix[i]) // wc > perro.txt
	{
		if (is_redirection(minishell->input_matrix[i], 0))
		{
			set_redir_type(minishell, minishell->input_matrix[i]);
			process_child_block(minishell, &i);
			i--;
		}
		i++;
	}
	if (minishell->redirection)
		minishell->input_matrix = clean_matrix_redirs(minishell);
}
/********************************************* */
static void	redirect_parent(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->first_cmd > 0)
		set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
	while (minishell->input_matrix[i])
	{
		if (is_redirection(minishell->input_matrix[i], 0))
		{
			set_redir_type(minishell, minishell->input_matrix[i]);
			process_parent_block(minishell, &i);
			//fprintf(stderr, "Al salir del procesado vale: %d\n", i);
			i--; // PROVISIONAL - Funciona con esto pero sirve solo para casos concretos
			// Probablemente flag
		}
		i++; // SEGFAULT AQUÍ [Ya no lo da, revisar el decremento de arriba]
	}
	if (minishell->redirection)
		minishell->input_matrix = clean_matrix_redirs(minishell);
}
/************************************************ */
void	process_child_block(t_minishell *minishell, int *index)
{
	//contempla todo menos la pipe porque separamos por pipes por defecto
	if (minishell->input_matrix[*index][0] == REDIR_OUT)
		ft_redir_out(minishell, index);
	//minishell->input_matrix = clean_matrix_redirs(minishell);
}

void	process_parent_block(t_minishell *minishell, int *index)
{
	//contempla todo menos la pipe porque separamos por pipes por defecto
	if (minishell->input_matrix[*index][0] == REDIR_OUT)
		ft_redir_out_parent(minishell, index);
	//minishell->input_matrix = clean_matrix_redirs(minishell);
}

/*
ft_redir_out()
{
	int	fd;

	i++;
	fd = create_empty_file(minishell->input_matrix[i]);
	if (si la sig no es un redir out o no existe)
		if (si la sig es ">>")
			//excepcion
		pipe_to_file(STDOUT_FILENO, fd);
	close(fd);
}

ft_redir_append()
{
	int	fd;

	i++;
	fd = open(minishell->input_matrix[i], O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		perror();
		return ;
	}
	if (si la sig no es un redir append o no existe)
		if (si la sig es ">")
			//excepcion
		pipe_to_file(STDOUT_FILENO, fd);
	close(fd);
}

ft_redir_in() // wc < hola.txt
{
	int	fd;

	if (!check_file_in_matrix(minishell->input_matrix)) // checkea validez de todos los files
	{
		//
	}
	while (minishell->input_matrix[i])
	{
		if (is_redirection(minishell->input_matrix[i], 0))
			if (si encuentro una redireccion igual)
		i++;
	}
	//fd = open(minishell->input_matrix[], O_RDONLY);
}

ft_heredoc()
{
	//bloque de excalidraw1
	//bloque de excalidraw2
	//bloque de excalidraw3
	Apunte: podríamos usar TEMP_PIPE en lugar de un .txt, solo hay que hacer:
	escribir ft_putendl_fd(readline, temp_pipe)
	set_pipe_mode(STDIN_FILENO, temp_pipe) y cogería el input de esa pipe
	haciendo esto no tendríamos que crear archivo y luego borrarlo tras su uso
	revisarlo porque justo en la sig. linea he puesto con los heredoc_fds
	
	set_pipe_mode(STDIN_FILENO, minishell->heredoc_fds[minishell->heredoc.heredoc_num])
	minishell->heredoc.heredoc_num++; 
}

static void	redirect_parent(t_minishell *minishell) // ultimo comando
{
	if (minishell->redirection == PIPE)
		set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
	else if (minishell->redirection == REDIR_OUT) // >
		ft_redir_out_parent(minishell);
	else if (minishell->redirection == REDIR_APPEND) // >>
		ft_redir_append_parent(minishell);
	else if (minishell->redirection == REDIR_IN) // <
		ft_redir_in_parent(minishell);
	else if (minishell->redirection == REDIR_HEREDOC) // <<
		ft_redir_heredoc_parent(minishell);
}*/

void	fd_redirection(int from, int to)
{
	if (dup2(to, from) == -1)
	{
		perror("dup2: error duplicating fd");
		exit(EXIT_FAILURE);
	}
}

void	store_fd(t_minishell *minishell)
{
	minishell->pipe_tools.STDIN = dup(STDIN_FILENO);
	minishell->pipe_tools.STDOUT = dup(STDOUT_FILENO);
}

void	reset_fd(t_minishell *minishell)
{
	if (minishell->redirection)
	{
		fd_redirection(STDIN_FILENO, minishell->pipe_tools.STDIN);
		fd_redirection(STDOUT_FILENO, minishell->pipe_tools.STDOUT); // para resetear la salida ya que si sale con "ls > file" el stdout
		//se quedaba en file, ya que esto lo hacia antes un hijo pero ahora lo hace el padre
		close(minishell->pipe_tools.STDIN);
		close(minishell->pipe_tools.STDOUT);
	}
}

void	pipe_append(t_minishell *minishell, t_pipe *pipe)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = malloc((minishell->pipe_tools.redir_count) * sizeof(t_pipe));
	if (!tmp)
	{
		perror("malloc");
		return ;
	}
	while (i < minishell->pipe_tools.redir_count - 1)
	{
		tmp[i] = minishell->pipe_tools.pipes[i];
		i++;
	}
	tmp[i] = *pipe;
	if (minishell->pipe_tools.pipes)
		free(minishell->pipe_tools.pipes);
	minishell->pipe_tools.pipes = tmp;
}
