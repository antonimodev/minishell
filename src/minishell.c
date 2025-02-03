#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char	*input;
	char	**input_matrix;

    while (1)
    {
		input = NULL;
		while (!input || !input[0])
		    input = readline("minishell> ");
		add_history(input);
		input_matrix = ft_split(input, ' ');
		if (ft_strcmp(input_matrix[0], "exit") == 0)
		{
			free(input); // liberamos input antes de pisarlo
			free_matrix(input_matrix); // liberamos input_matrix al terminar el programa
			return (1);
		}
		execute(input_matrix, envp);
		free(input);
		free_matrix(input_matrix);
    }
    return (0);
}

//execve(char *pathname, (flags, argumentos), envp)
//execve(char *pathname, char *const argv[], char *const envp[]);