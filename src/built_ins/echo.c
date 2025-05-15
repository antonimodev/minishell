/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:40:29 by antonimo          #+#    #+#             */
/*   Updated: 2025/04/24 13:29:01 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_valid(const char *str) // cambiar nombre
{
    int i;

	i = 1;
    if (str[0] != '-' || str[1] == '\0') // no es valido false
        return (false);
    while (str[i]) //mientras que sea n continua "-nnnnnn"
    {
        if (str[i] != 'n')
            return (false);
        i++;
    }
    return (true);
}

void    ft_echo(t_minishell *minishell)
{
    int     i;
    bool    flag;

    i = 1;
    flag = false;
    while (minishell->input_matrix[i] && is_valid(minishell->input_matrix[i])) // si es correcto continua y flg true
    {
        flag = true;
        i++;
    }
    while (minishell->input_matrix[i]) //imprimir siguiente de -n
    {
        printf("%s", minishell->input_matrix[i]);
        if (minishell->input_matrix[i + 1]) //si hay siguiente
            printf(" "); //imprime espacio
        i++;
    }
    if (!flag) //no hay -n que sea valido
        printf("\n");
}
