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

static void		handle_sign(int signal)
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
