#include "minishell.h"

char	**clean_split(t_tokenizer *split)
{
    char	**new;
    int		i;
    int		len;

    i = 0;
    new = malloc(sizeof(char *) * (ft_strlen(split->matrix[i]) + 1));
    if (!new)
        return (NULL);
    i = -1;
    while (split->matrix[++i])
    {
        len = ft_strlen(split->matrix[i]) + 1;
        new[i] = malloc(sizeof(char) * len);
        if (!new[i])
        {
            free_matrix_error(new, i);
            return (NULL);
        }
        ft_strlcpy(new[i], split->matrix[i], len);
        free(split->matrix[i]);
    }
    new[i] = NULL;
    free(split->matrix);
    return (new);
}

char **custom_split(char *user_input)
{
    t_tokenizer split;
    int len;
	int	i;

	i = 0;
    split.matrix_index = 0;
    len = (int)ft_strlen(user_input) + 1;
    split.matrix = malloc(sizeof(char *) * len);
	if (!split.matrix)
		return (NULL);
    /* for (int i = 0; i < len; i++)
        split.matrix[i] = NULL; */
	while (i < len)
		split.matrix[i++] = NULL;
    fill_tokens(user_input, &split);
    split.matrix[split.matrix_index] = NULL;
    return clean_split(&split);
}

void	fill_tokens(char *user_input, t_tokenizer *split)
{
    int		i;
    char	*word; // str para almacenar palabras

    i = 0;
    while (user_input[i]) // 'l"s"'
    {
        while (user_input[i] == ' ') // limpia los espacios
            i++;
        if (!user_input[i]) // proteger user_input = "    " solo espacios
            break ;        
        word = build_token(user_input, &i);
        split->matrix[split->matrix_index] = word;
        split->matrix_index++;
    }
}

/* -------------------- */
void handle_quotes(char *str, int *i, t_token_state *state)
{
    if (!state->in_quotes) // Si no está en comillas
    {
        state->in_quotes = true; // Comillas true
        state->current_quote = str[*i]; // detectamos que tipo de comilla es
        (*i)++;
    }
    else if (str[*i] == state->current_quote) // si es la comilla de antes
    {
        state->in_quotes = false; // Comillas cerradas
        state->current_quote = '\0'; // inicializacion a null
        (*i)++;
    }
    else
    {
        state->token[state->j++] = str[*i];
        (*i)++;
    }
}

char *build_token(char *user_input, int *i_pos)
{
    t_token_state state;
    int i;

    i = *i_pos;
    state.token = malloc(ft_strlen(user_input) + 1); // revisar para sacar el len exacto para el rendimiento
    if (!state.token)
        return (NULL);
    // inicializacion de struct
    state.j = 0;
    state.in_quotes = false;
    state.current_quote = '\0';
    while (user_input[i])
    {
        if (!state.in_quotes && (user_input[i] == ' '))
            break;
        if (user_input[i] == '"' || user_input[i] == '\'')
            handle_quotes(user_input, &i, &state);
        else
            state.token[state.j++] = user_input[i++];
    }
    state.token[state.j] = '\0';
    *i_pos = i;
    return (state.token);
}
