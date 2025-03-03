/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/03 13:55:49 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
