//prueba

// se debe compilar con -lreadline, poner en el makefile
#include "minishell.h"

char	*cmdcat(char *path, char *cmd)
{
	char	*filepath;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	filepath = malloc (path_len + cmd_len + 2 * sizeof(char));
	if (!filepath)
		return (NULL);
	filepath = ft_strcpy(filepath, path);
	filepath = ft_strcat(filepath, "/");
	filepath = ft_strcat(filepath, cmd);
	return (filepath);
}

//funcion propia strcpy para poder concatenar
char	*ft_strcpy(char *dest, const char *src)
{
	char *start;
	
	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}

char	*ft_strcat(char *dest, const char *src)
{
    char *start = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return (start);
}

void	foo(void)
{
	char	*path;
	char	**path_split;

	//comprobar strchr de "/", comprobar con stat y si es true, return strdup(cmd)
	//utilizar stat() en caso de que sea ruta relativa
	//usar access(F_OK, X_OK) para existencia y permisos
	path = getenv("PATH");
	path_split = ft_split(path, ':');
	//concatenar
	print_matrix(path_split);
}

int main(void)
{
    char	*input;
    // Si existe, imprime (es una prueba)
	//foo();
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
//execve(char *pathname, matriz con ruta, flags, argumentos), envp)