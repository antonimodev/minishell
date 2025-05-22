/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jortiz-m <jortiz-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:12:06 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/05/22 11:12:50 by jortiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_UTILS_H
# define MATRIX_UTILS_H

# include "libft.h"

/* ------------------------------ CREATE_MATRIX  */
char	**create_matrix(int n);

/* ------------------------------ MATRIX_APPEND  */
char	**matrix_append(char **matrix, char *new_str);

/* ------------------------------ MATRIX_SUBSTRACT  */
char	**matrix_substract(char **matrix, unsigned int index);

/* ------------------------------ MATRIX_CPY ------------------------------ */
char	**matrix_cpy(char **src, int extra_slots);

/* ------------------------------ FREE_MATRIX  */
void	free_matrix(char **matrix);
void	free_matrix_error(char **matrix, int i);

/* ------------------------------ MATRIX_LEN  */
int		matrix_len(char **matrix);

/* ------------------------------ PRINT_MATRIX  */
void	print_matrix(char **matrix);

/* ------------------------------ MATRIX_REPLACE  */
void	matrix_replace(char **matrix, int index, char *new_value);

/* ------------------------------ MATRIX_FROM_MATRIX  */
char	**matrix_from_matrix(char **src_matrix, int start, int end);
#endif