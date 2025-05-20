#include "minishell.h"

static void	redir_heredoc(t_minishell *minishell, int index);
static void	redir_in(t_minishell *minishell, int index);
static void	redir_append(t_minishell *minishell, int index);
static void	redir_out(t_minishell *minishell, int index);
static void	process_redir(t_minishell *minishell);
static void	set_last_redirs(t_minishell *minishell, int index);

static bool check_heredoc_presence(t_minishell *minishell);
static void	handle_parent_pipe(t_minishell *minishell, bool has_heredoc);
static void handle_child_pipe(t_minishell *minishell, bool has_heredoc);

static bool check_heredoc_presence(t_minishell *minishell)
{
	int i;

	i = 0;
	while (minishell->input_matrix[i])
	{
		if (ft_test(minishell->input_matrix[i], "<<"))
			return true;
		i++;
	}
	return false;
}

static void	handle_parent_pipe(t_minishell *minishell, bool has_heredoc)
{
	if (minishell->pid == PARENT)
	{
		if (minishell->first_cmd == 1)
			minishell->first_cmd++;
		if (minishell->first_cmd > 1 && !has_heredoc)
			set_pipe_mode(STDIN_FILENO, minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
	}
}

static void handle_child_pipe(t_minishell *minishell, bool has_heredoc)
{
	if (minishell->pid == CHILD)
	{
		if (minishell->first_cmd == 1 && !has_heredoc)
			redir_first_cmd(minishell);
		else if (minishell->first_cmd > 1 && !has_heredoc)
			ft_pipe(minishell);
	}
}

void new_redirect(t_minishell *minishell)
{
    int		i;
	bool	has_heredoc;

	has_heredoc = check_heredoc_presence(minishell);
	handle_parent_pipe(minishell, has_heredoc);
	handle_child_pipe(minishell, has_heredoc);
	i = 0;

	while (minishell->input_matrix[i])
	{
		if (new_is_redirection(minishell->input_matrix[i]))
		{
			minishell->redir_existence = true;
			set_last_redirs(minishell, i);
		}
		i++;
	}
	process_redir(minishell);
	if (minishell->pid == CHILD && has_heredoc)
		set_pipe_mode(STDOUT_FILENO,
			minishell->pipe_tools.pipes[minishell->pipe_tools.redir_count - 1]);
	if (minishell->redir_existence)
		minishell->input_matrix = clean_matrix_redirs(minishell);
}

static void	set_last_redirs(t_minishell *minishell, int index)
{
	int	last_fd;

	last_fd = index + 1;
	if (ft_test(minishell->input_matrix[index], "<"))
		minishell->last_input = last_fd;
	if (ft_test(minishell->input_matrix[index], "<<"))
	{
		minishell->last_input = last_fd;
		if (!minishell->heredoc.delimits)
			minishell->heredoc.delimits = create_matrix(0);
		minishell->heredoc.delimits = matrix_append(minishell->heredoc.delimits, minishell->input_matrix[last_fd]);
	}
	if (ft_test(minishell->input_matrix[index], ">")
	||	ft_test(minishell->input_matrix[index], ">>"))
		minishell->last_output = last_fd;
}

static void	process_redir(t_minishell *minishell)
{
	int	i;

	i = 0;
	while(minishell->input_matrix[i])
	{
		if (ft_test(minishell->input_matrix[i], "<<"))
			redir_heredoc(minishell, i);
		i++;
	}
	i = 0;
	while(minishell->input_matrix[i])
	{
		if (ft_test(minishell->input_matrix[i], ">>"))
			redir_append(minishell, i);
		else if (ft_test(minishell->input_matrix[i], ">"))
			redir_out(minishell, i);
		else if (ft_test(minishell->input_matrix[i], "<")) // antes ft_strcmp == 0
			redir_in(minishell, i);
		i++;
	}
}

static void	redir_out(t_minishell *minishell, int index)
{
	int	file;
	int	last_fd;

	last_fd = index + 1;
	file = open(minishell->input_matrix[last_fd], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->invalid_input = true;
		return ;
	}
	if (minishell->last_output == last_fd)
		fd_redirection(STDOUT_FILENO, file);
	close(file);
}

static void	redir_append(t_minishell *minishell, int index)
{
	int	file;
	int	last_fd;

	last_fd = index + 1;
	file = open(minishell->input_matrix[last_fd], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->invalid_input = true;
		return ;
	}
	if (minishell->last_output == last_fd)
		fd_redirection(STDOUT_FILENO, file);
	close(file);
}

static void	redir_in(t_minishell *minishell, int index)
{
	int	last_fd;
	int	file;
	
	last_fd = index + 1;
	if (access(minishell->input_matrix[last_fd], F_OK | R_OK) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(minishell->input_matrix[last_fd], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->invalid_input = true;
		return ;
	}
	file = open(minishell->input_matrix[last_fd], O_RDONLY, 444);
	if (file < 0)
	{
		perror("error al abrir en redir_in");
		return ;
	}
	if (minishell->last_input == last_fd)
		fd_redirection(STDIN_FILENO, file);
	close(file);
}

static bool is_delimiter(t_minishell *minishell, char *line)
{
    if (ft_strcmp(line, minishell->heredoc.delimits[minishell->heredoc.delimit_index]) == 0)
    {
        free(line);
        minishell->heredoc.delimit_index++;
        return (true);
    }
    return (false);
}

static void handle_heredoc_eof(t_minishell *minishell)
{
    printf("minishell: warning: here-document delimited by end-of-file (wanted '%s')\n", 
            minishell->heredoc.delimits[minishell->heredoc.delimit_index]);
    minishell->heredoc.delimit_index++;
}

// ls << EOF1 > output.txt > output2.txt << EOF2 >> output3.txt | echo "hola" << EOF3 | wc << EOF4
static void	redir_heredoc(t_minishell *minishell, int index)
{
	int		last_fd;
	char	*line;
	t_pipe	temp_pipe;

	last_fd = index + 1;
	if (minishell->last_input == last_fd)
		temp_pipe = create_pipe();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			handle_heredoc_eof(minishell);
			break ;
		}
		else if (is_delimiter(minishell, line))
			break ;
		if (minishell->last_input == last_fd && !minishell->invalid_input)
			ft_putendl_fd(line, temp_pipe.write_pipe);
		free(line);
	}
	if (minishell->last_input == last_fd && !minishell->invalid_input)
		set_pipe_mode(STDIN_FILENO, temp_pipe);
}
