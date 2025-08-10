#include "minishell.h"

char *extract_word(char *str, int *index)
{
    int i = *index;
    // Skip leading whitespace
    while (str[i] && is_whitespace(str[i]))
        i++;
    if (!str[i])
        return NULL;
    int start = i;
    // Find end of word
    while (str[i] && !is_whitespace(str[i]))
        i++;
    *index = i;
    return ft_substr(str, start, i - start);
}
