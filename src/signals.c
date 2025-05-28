/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:42:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/05/20 12:59:12 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SEÑALES JULIA */

/* static void		handle_sign(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void		child_sign(int signal)
{
	if (signal == SIGINT)
		g_signal = 130;
	else if(signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		g_signal = 131;
	}
	return ;
}

void	setup_signals(int signal)
{
	struct sigaction	sa;

	if(signal)
		sa.sa_handler = &handle_sign;
	else
		sa.sa_handler = &child_sign;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
*/

/* SEÑAL QUE HABIA DE ANTES */

/* READLINE NO SE CIERRA NUNCA, RL_REDISPLAY SOLAMENTE MUESTRA LO QUE CONTENIA
EL ULTIMO READLINE, NUNCA LO CIERRA NI TE PIDE UN SEGUNDO READLINE, ES COMO REPETIR
UN PRINTF DEL ULTIMO PROMPT */
static void	handle_sign(int sign)
{
	if (sign == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("soy el SIGINT:\n");
		rl_redisplay();
	}
}

void	setup_signals (void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = &handle_sign;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction");

	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction");
}


void	set_std_signals(void)
{
	struct sigaction sa_child;

	sa_child.sa_handler = SIG_DFL;
	sa_child.sa_flags = 0;
	sigemptyset(&sa_child.sa_mask);
	sigaction(SIGINT, &sa_child, NULL);
	sigaction(SIGQUIT, &sa_child, NULL);
}