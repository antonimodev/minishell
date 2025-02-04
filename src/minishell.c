#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_input	input;

    while (1)
    {
		get_input(&input);
		execute(&input, envp);
		free_input(&input);
    }
    return (0);
}

void	free_input(t_input *input)
{
	free(input->user_input);
	free_matrix(input->input_matrix);
}

void get_input(t_input *input)
{
	ft_memset(input, 0, sizeof(t_input));
	while (!valid_input(input->user_input))
	{
	    input->user_input = readline("minishell> ");
		add_history(input->user_input);
	}
}
bool	valid_input(char *input)
{
    if (!input || input[0] == '\0')
	{
		free(input);
		return (false);
	}
	else if ((ft_strcmp(input, "exit") == 0))
	{
		free(input);
        exit(EXIT_FAILURE);
	}
    return true;
}


//execve(char *pathname, (flags, argumentos), envp)
//execve(char *pathname, char *const argv[], char *const envp[]);