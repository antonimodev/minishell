#include "minishell.h"

int main(void)
{
    char	*input;
    while (1)
    {
    	input = readline("minishell> ");   // Leer una línea de entrada del usuario
		add_history(input); // Añade input al historial de comandos introducidos
		execute(input);
		if (ft_strcmp(input, "exit") == 0)
			break;
		free(input); // liberamos input antes de pisarlo
    }
	free(input); // Liberamos input al terminar el programa
    return (0);
}

//execve(char *pathname, (flags, argumentos), envp)
//execve(char *pathname, char *const argv[], char *const envp[]);