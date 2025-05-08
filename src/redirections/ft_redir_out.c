/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:27 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/29 13:03:37 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pipe_to_file: escribe el contenido de un pipe a un archivo
//set_pipe_mode: establece el modo de una pipe (lectura o escritura)

// Nombre provisional, la idea es crear un archivo vacio y cerrarlo
// al cerrarlo en la misma funcion no suele ser muy generica la funcion.
static void	create_empty_file(int *file, char *filename)
{
	*file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (*file == -1)
    {
        perror("Error al abrir el archivo");
        return;
    }
}

void	ft_redir_out_parent(t_minishell *minishell, int *index)
{
	//fprintf(stderr, "\nRedir out PARENT:\n"); // ls > test
	int		file;

	(*index)++;// pasa de ">" a test
	while (minishell->input_matrix[*index])
	{
		create_empty_file(&file, minishell->input_matrix[*index]);
		(*index)++; // pasa de test a ">"
		if (minishell->input_matrix[*index] &&
		minishell->input_matrix[*index][0] == REDIR_OUT)
		{
			close(file);
			(*index)++; // pasa de > a "perro"
		}
		else
		{
			fd_redirection(STDOUT_FILENO, file);
			//fprintf(stderr, "\nSe ha redireccionado STDOUT al fd: %d\n", file);
			close(file);
		}
	}
	//fprintf(stderr, "\nSe han hecho todos los '>':\n"); // ls > test
	// Cuando esté ">>" hay que reestructurar para que funcione: "ls > empty >> untouch > empty2 >> untouch2 > final"
	// En ese ejemplo, final tiene el resultado de LS, empty/empty2 se vacian y untouch/untouch2 no se modifican
}

void	ft_redir_out(t_minishell *minishell, int *index) // ls > file1 | ls > file2
{
	int		file;

	(*index)++;
	while (minishell->input_matrix[*index])
	{
		create_empty_file(&file, minishell->input_matrix[*index]);
		(*index)++;
		if (minishell->input_matrix[*index] &&
			minishell->input_matrix[*index][0] == REDIR_OUT)
		{
			close(file);
			(*index)++;
		}
		else
		{
			fd_redirection(STDOUT_FILENO, file);
			close(file);
		}
	}
}

// TESTING INCORPORANDO LA FUNCION DE ">>"

void	ft_redir_out_parent(t_minishell *minishell, int *index)
{
	//fprintf(stderr, "\nRedir out PARENT:\n"); // ls > test
	int		file;

	(*index)++;// pasa de ">" a test
	while (minishell->input_matrix[*index])
	{
		create_empty_file(&file, minishell->input_matrix[*index]);
		(*index)++; // pasa de test a ">"
		if (minishell->input_matrix[*index] &&
		minishell->input_matrix[*index][0] == REDIR_OUT)
		{
			close(file);
			(*index)++; // pasa de > a "perro"
		}
		else
		{
			fd_redirection(STDOUT_FILENO, file);
			//fprintf(stderr, "\nSe ha redireccionado STDOUT al fd: %d\n", file);
			close(file);
		}
	}
	//fprintf(stderr, "\nSe han hecho todos los '>':\n"); // ls > test
	// Cuando esté ">>" hay que reestructurar para que funcione: "ls > empty >> untouch > empty2 >> untouch2 > final"
	// En ese ejemplo, final tiene el resultado de LS, empty/empty2 se vacian y untouch/untouch2 no se modifican
}

/* testeo fd append para leer todo el bloque e ir creando files */
void	fd_append(t_minishell *minishell, int fd)
{
	int	*array_tmp;
	int	i;

	array_tmp = malloc((minishell->pipe_tools.fd_count + 1) * sizeof(int));
	if (!array_tmp)
	{
		perror("malloc fd_append");
		return ;
	}
	i = 0;
	while (i < minishell->pipe_tools.fd_count)
	{
		array_tmp[i] = minishell->pipe_tools.array_fd[i];
		i++;
	}
	array_tmp[i] = fd;
	free(minishell->pipe_tools.array_fd);
	minishell->pipe_tools.array_fd = array_tmp;
	minishell->pipe_tools.fd_count++;
}

void	close_fd(t_minishell *minishell)
{
	int	i;

	i = minishell->pipe_tools.fd_count - 1;
	while (i >= 0)
	{
		close(minishell->pipe_tools.array_fd[i]);
		i--;
	}
}

{
	while (minishell->input_matrix[i])
	{
		if (is_redirection(minishell->input_matrix[i], 0))
		{

		}
	}
}

void	redir_out_append(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->input_matrix[i])
	{
		if (ft_test(minishell->input_matrix[i] == ">"))
		{
			//i++;
			// create_trunc_file(minishell->input_matrix[i]) tmb se añade a minishell->pipe_tools.array_fd y fd_count++;
		}
		else if (ft_test(minishell->input_matrix[i]) == ">>")
		{
			//i++;
			// create_append_file() tmb se añade a minishell->pipe_tools.array_fd y fd_count++;
		}
		i++;
	}
}
