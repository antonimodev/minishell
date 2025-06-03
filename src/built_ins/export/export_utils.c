/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:09:48 by jortiz-m          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:09 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_chr_from_str(char *str, char chr)
{
	char	*new_str;
	bool	copy;
	int		i;
	int		j;

	new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	copy = false;
	while (str[i])
	{
		if (str[i] != chr || copy)
		{
			new_str[j] = str[i];
			j++;
		}
		if (str[i] == chr)
			copy = true;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	get_chr_index(char *str, char chr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strjoin_at(const char *s1, const char *s2, size_t pos)
{
	size_t		len1;
	size_t		len2;
	char		*new_str;

	len1 = (size_t)ft_strlen(s1);
	len2 = (size_t)ft_strlen(s2);
	if (pos > len1)
		pos = len1;
	new_str = malloc(len1 + len2 + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, s1, pos);
	ft_memcpy(new_str + pos, s2, len2);
	ft_memcpy(new_str + pos + len2, s1 + pos, len1 - pos);
	new_str[len1 + len2] = '\0';
	return (new_str);
}

char	*get_envp_var_name(char *env_var)
{
	char	*var_name;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '+' && env_var[i] != '=')
		i++;
	var_name = ft_substr(env_var, 0, i);
	return (var_name);
}

bool	find_in_matrix(char **matrix, char *var_name, int *index)
{
	*index = 0;
	while (matrix && matrix[*index])
	{
		if (!ft_strncmp(matrix[*index], var_name, ft_strlen(var_name))
			&& (matrix[*index][ft_strlen(var_name)] == '='
			|| matrix[*index][ft_strlen(var_name)] == '\0'))
			return (true);
		(*index)++;
	}
	return (false);
}
