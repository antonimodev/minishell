#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct s_tokenizer
{
    char	**tokens;
    int		token_idx;
}	t_tokenizer;

/*
 * build_token:
 *   Construye un token de la string 'str' a partir del índice *pi.
 *   El token se construye quitando las comillas (simples o dobles),
 *   permitiendo combinar partes entrecomilladas y sin comillas.
 */
static char	*build_token(char *str, int *pi)
{
    int		i;
    int		j;
    bool	in_quotes;
    char	current_quote;
    char	*token;

    i = *pi;
    j = (int)strlen(str);
    token = malloc(j + 1);
    if (!token)
        return(NULL);
    j = 0;
    in_quotes = false;
    current_quote = '\0';
    while (str[i])
    {
        if (!in_quotes && (str[i] == ' '))
            break;
        if (str[i] == '"' || str[i] == '\'')
        {
            if (in_quotes == false)
            {
                in_quotes = true;
                current_quote = str[i];
                i++;
            }
            else if (str[i] == current_quote)
            {
                in_quotes = false;
                current_quote = '\0';
                i++;
            }
            else
                token[j++] = str[i++];
        }
        else
            token[j++] = str[i++];
    }
    token[j] = '\0';
    *pi = i;
    return (token);
}

/*
 * fill_tokens:
 *   Recorre la cadena 'str' y llena el arreglo de tokens en 'tz->tokens'
 *   utilizando build_token para separar cada token.
 */
static int	fill_tokens(char *str, t_tokenizer *tz)
{
    int     i;
    int     count;
    char	*token;

    i = 0;
    count = 0;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (!str[i])
            break ;
        token = build_token(str, &i);
        tz->tokens[tz->token_idx] = token;
        tz->token_idx = tz->token_idx + 1;
        count++;
        while (str[i] == ' ')
            i++;
    }
    return (count);
}

/*
 * custom_split:
 *   Separa la cadena 'str' en tokens siguiendo las reglas de bash.
 *   Las comillas se eliminan, y se combinan partes entrecomilladas y sin comillas.
 */
char	**custom_split(char *str)
{
    int			max_tokens;
    t_tokenizer	tz;

    max_tokens = (int)strlen(str) + 1;
    tz.tokens = malloc(sizeof(char *) * (max_tokens));
    if (!tz.tokens)
        return(NULL);
    tz.token_idx = 0;
    (void)fill_tokens(str, &tz);
    tz.tokens[tz.token_idx] = NULL;
    return (tz.tokens);
}

/*
 * main: Ejecuta pruebas con variadas combinaciones de comillas y espacios.
 * Los casos de prueba incluyen:
 *   - Comandos sin comillas.
 *   - Comandos con argumentos entrecomillados (simples o dobles).
 *   - Comandos mixtos, por ejemplo: "ls" seguido de "-l -a" dentro de comillas.
 *   - Casos con espacios redundantes.
 */
int	main(void)
{
    char	*tests[] = {
        "ls",
        "ls -l",
        "ls '-la'",
        "echo \"Hello World\"",
        "grep \"pattern\" file",
        "'single quoted'",
        "\"double quoted\"",
        "ls \"-l -a\"",
        "  ls   -l   ",
        "echo 'He said \"hi\"'",
        "\" l\"s",
        "l\"s\" -l"
    };
    int		test_count;
    int		i;
    char	**args;
    int		j;

    test_count = (int)(sizeof(tests) / sizeof(tests[0]));
    i = 0;
    while (i < test_count)
    {
        printf("Test %d: %s\n", i + 1, tests[i]);
        args = custom_split(tests[i]);
        j = 0;
        while (args[j])
        {
            printf(" [%s]", args[j]);
            free(args[j]);
            j = j + 1;
        }
        printf("\n\n");
        free(args);
        i = i + 1;
    }
    return (0);
}
