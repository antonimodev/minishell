//prueba

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
// #include "minishell.h"
// se debe compilar con -lreadline, poner en el makefile

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
