//prueba

// se debe compilar con -lreadline, poner en el makefile
#include "minishell.h"

void	foo(void)
{
	char	*path;
	char	**path_split;

	path = getenv("PATH");
	path_split = ft_split(path, ':');
}

int main(void)
{
    char *input;
    // Si existe, imprime (es una prueba)
    while (1)
    {
    	input = readline("minishell> ");   // Leer una línea de entrada del usuario
		add_history(input); // Añade input al historial de comandos introducidos
        printf("You entered: %s\n", input);
		if (strcmp(input, "exit") == 0)
			break;
    }
	free(input); // Liberar la memoria asignada por readline
    return (0);
}

// char	*path -> getenv("PATH");
// char	**path_split -> ft_split(path, ':');
//execve(char *pathname,))