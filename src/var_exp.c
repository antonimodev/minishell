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
	// Buscar $ -> Si lo encuentra, empezar a concatenar en un string para almacenar el nombre de la var
	// Cada vez que se concatena, se comprueba si existe con getenv.
	// 		Si existe -> getenv del nombre, sustituimos desde el $ hasta la terminacion de la variable con 
	// 					 el valor que tenga en el env y seguimos buscando y concatenando Ej: $HOME!$PATH
	//		No existe -> seguimos concatenando hasta encontrar un caracter que termine el str ( espacios o catacteres invalidos )
	// ESTA RODEADO POR COMILLAS SIMPLES? -> Si, return ;
}

/* MIRAR INPUT */


/*
"$PATH"		-> Si se puede hacer
"${PATH}"	-> Si se puede hacer
${PATH}		-> Si se puede hacer
"$PATH"		-> Si se puede hacer
$PATH		-> Si se puede hacer
$PATH$HOME	-> Si se puede hacer
$HOME!		-> Si, devuelve home y al final concatena el !

$HOME!$PATH	-> wtf?
-----------------------------------------

"'$PATH'"	-> No se puede hacer
"$"PATH		-> No se puede hacer
"${"PATH"}"	-> No se puede hacer
"${PATH"	-> No se puede hacer
*/