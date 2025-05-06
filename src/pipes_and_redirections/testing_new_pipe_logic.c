void	extract_blocks(t_minishell *minishell)
{
	int		i;
	int		operator_pos;
	char	**matrix;
 
	i = 0;
	operator_pos = 0;
	matrix = split_input(minishell);

	while (matrix[i])
	{
		if (ft_strchr(matrix[i], '|')) // cat > file.txt << EOF | wc 
		{
            // probablemente pongamos ft_test/strchr para evitar crear '|' si no va a usarse como output
            add_redir(minishell); // pipe de resultado de bloque
			if (process_child_cmd(minishell, matrix, &operator_pos, &i))
			{
				free_matrix(matrix);
				return ;
			}
		}
		i++;
	}
    //si soy padre
    minishell->input_matrix = matrix_from_matrix(matrix, operator_pos,
        matrix_len(matrix));
    free_matrix(matrix);
}

/*set_redir_type(minishell, matrix[i]);

set_parent_input(minishell);*/


static bool	process_child_cmd(t_minishell *minishell, char **matrix,
	int *operator_pos, int *current_pos)
{
	pid_t	child;

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
    return (false);
}
