#include "minishell.h"

/* 
Manejar CTRL + C -> (SIGINT) - DETIENE EJECUCION 
Manejar CTRL + D -> (EOF) La condición que maneja es si user_input == NULL - EXIT TERMINAL
Manejar CTRL + \ -> NADA
*/

void handle_sign(int sign)
{
    UNUSED(sign);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
	//aqui deberia de imprimir la funcion shell_prompt()
    rl_redisplay();
}

void setup_signals(void)
{
    struct sigaction sa;

    sa.sa_sigaction = &handle_sign;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
}
