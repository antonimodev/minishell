/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:13:10 by antonimo          #+#    #+#             */
/*   Updated: 2025/03/07 12:14:47 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	chr_index(char *str, char c);
/* Debemos de añadir una flag en t_minishell para ver si debemos expandir o no la variable*/

void	valid_expansion_var(t_minishell *minishell) // Probablemente si es true, devuelve env_var
{
	char	*env_var;

	if (!ft_strchr_gnl(minishell->user_input, '$')) // Buscar $ -> Si lo encuentra, empezar a concatenar en un string para almacenar el nombre de la var
		return ;
	if (!expansion_quotes_var(minishell))
		return ;
	// Cada vez que se concatena, se comprueba si existe con getenv.
	// 		Si existe -> getenv del nombre, sustituimos desde el $ hasta la terminacion de la variable con 
	// 					 el valor que tenga en el env y seguimos buscando y concatenando Ej: $HOME!$PATH
	//		No existe -> seguimos concatenando hasta encontrar un caracter que termine el str ( espacios o catacteres invalidos )
	// ESTA RODEADO POR COMILLAS SIMPLES? -> Si, return ;
}

bool	expansion_quotes_var(t_minishell *minishell)
{
	t_quote	quote;
	unsigned int	i;

	quote.type = '\0';
	quote.closed = true;
	i = 0;

	i = chr_index(minishell->user_input, '$');
	if (!i)
		return (false);

	return (prev(&quote, i, minishell->user_input)
		&& post(&quote, i, minishell->user_input));
}
/*
	echo "       'hola ' $HOME "
	echo "       'hola ' '$HOME'" el resultado de esta es que no estan cerradas las comillas cuando si lo estan con prev y post
*/

bool	prev(t_quote *quote, unsigned int index, char *str)
{
	while (index != 0)
	{
		quote_state(quote, index, str[index]);
		index--;
	}
	return (quote->closed);
}
bool	post(t_quote *quote, unsigned int index, char *str)
{
	while (str[index])
	{
		quote_state(quote, index, str[index]);
		index++;
	}
	return (quote->closed);
}
static int	chr_index(char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

//	$PITO$PATH
//  
//	word -> $PITO ft_strlcat(src, dst)

//	USER_INPUT = echo "Hola, mi ruta es "$HOME/trolleado""
// Hola,
// mi
// ruta
// es
// $PIYO/trolleado

/* MIRAR INPUT */

/*
"$PATH"		-> Si se puede hacer
"${PATH}"	-> Si se puede hacer
${PATH}		-> Si se puede hacer
"$PATH"		-> Si se puede hacer
$PATH		-> Si se puede hacer
$PATH$HOME	-> Si se puede hacer
$DONT_EXIST$PATH -> Si se puede hacer
$PIYO/trolleado -> Imprime "trolleado" y no se expande
$HOME!		-> Si, devuelve home y al final concatena el !

$HOME!$PATH	-> NO HAY QUE MANEJARLO
-----------------------------------------

"'$PATH'"	-> No se puede hacer
"$"PATH		-> No se puede hacer
"${"PATH"}"	-> No se puede hacer
"${PATH"	-> No se puede hacer
*/
