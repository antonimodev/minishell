#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    int fd;
    int stdin_copy;
    pid_t pid;

    // Abre el archivo que contiene los comandos de prueba
    fd = open("src/commands.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Guarda una copia del descriptor de archivo de la entrada estándar
    stdin_copy = dup(STDIN_FILENO);
    if (stdin_copy == -1)
    {
        perror("dup");
        close(fd);
        return 1;
    }

    // Crea un proceso hijo
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(fd);
        close(stdin_copy);
        return 1;
    }

    if (pid == 0)
    {
        // Redirige la entrada estándar al archivo de comandos
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(fd);
            close(stdin_copy);
            return 1;
        }
        close(fd);

        // Ejecuta minishell
        execl("./minishell", "minishell", NULL);
        perror("execl");
        return 1;
    }
    else
    {
        // Espera a que el proceso hijo termine
        wait(NULL);
        close(fd);

        // Restaura la entrada estándar
        if (dup2(stdin_copy, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(stdin_copy);
            return 1;
        }
        close(stdin_copy);

        // Ejecuta minishell nuevamente para permitir la entrada interactiva
        execl("./minishell", "minishell", NULL);
        perror("execl");
        return 1;
    }

    return 0;
}