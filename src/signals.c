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
    rl_redisplay();
}

void setup_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &handle_sign;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
}

void shell_prompt(t_minishell *minishell)
{
    minishell->shell_prompt.user = ft_strjoin(BOLD_TURQUOISE, minishell->user);
    minishell->shell_prompt.user = ft_strjoin_gnl(minishell->shell_prompt.user, RESET);

    minishell->shell_prompt.pwd = getcwd(NULL, 0);

    minishell->shell_prompt.arrow = ft_strdup(BOLD_GREEN " ➜ " RESET);

    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.user, minishell->shell_prompt.arrow);
	free(minishell->shell_prompt.arrow);

    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, minishell->shell_prompt.pwd);
    free(minishell->shell_prompt.pwd);
    
    minishell->shell_prompt.prompt = ft_strjoin_gnl(minishell->shell_prompt.prompt, BOLD_YELLOW " ✦ " RESET);
}
