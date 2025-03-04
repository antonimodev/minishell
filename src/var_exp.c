/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:13:10 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/04 13:52:52 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Debemos de añadir una flag en t_minishell para ver si debemos expandir o no la variable*/
void	valid_expansion_var(t_minishell *minishell)
{
	// BUSCAR $ -> Si lo encuentra, seguimos
	// SI LA VARIABLE DESPUES DE $ ES VALIDA -> Si lo es, seguimos
	// ESTA RODEADO POR COMILLAS SIMPLES? -> Si, return ;
}

/* MIRAR INPUT */


/*
"$PATH"		-> Si se puede hacer
"${PATH}"	-> Si se puede hacer
${PATH}		-> Si se puede hacer
"$PATH"		-> Si se puede hacer
$PATH		-> Si se puede hacer

-----------------------------------------

"'$PATH'"	-> No se puede hacer
"$"PATH		-> No se puede hacer
"${"PATH"}"	-> No se puede hacer
"${PATH"	-> No se puede hacer
*/