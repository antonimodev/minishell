/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:11:27 by frmarian          #+#    #+#             */
/*   Updated: 2025/04/11 14:11:29 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_redir_out(t_minishell *minishell)
{
    int file;

    file = open("", O_WRONLY, O_CREAT, O_TRUNC, 644);
    fd_redirection(STDOUT_FILENO, file);
}
