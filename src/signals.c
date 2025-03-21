/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/21 12:23:14 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Manejar CTRL + C -> (SIGINT) - DETIENE EJECUCION 
Manejar CTRL + D -> (EOF) La condición que maneja es si user_input == NULL - EXIT TERMINAL
Manejar CTRL + \ -> NADA
*/

/**
 * @brief Signal handler for SIGINT (Ctrl+C).
 *
 * This function handles the SIGINT signal, which is typically triggered by
 * pressing Ctrl+C. It stops the current execution, moves to a new line,
 * and redisplays the prompt.
 *
 * @param sign The signal number (unused).
 */
void handle_sign(int sign)
{
    UNUSED(sign);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/**
 * @brief Sets up signal handling for the minishell.
 *
 * This function sets up the signal handler for SIGINT using `sigaction`.
 * It configures the signal action to use the `handle_sign` function.
 */
void setup_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &handle_sign;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
}
