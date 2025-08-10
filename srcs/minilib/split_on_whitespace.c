#include "minishell.h"

char **split_on_whitespace(char *str)
{
    int word_count;
    char *word;
    char **result;
    int word_idx; 
    int i; 
    
    result = init_split_array(str, &word_count);
    if (!result)
        return NULL;
    word_idx = 0;
    i = 0;
    while ((word = extract_word(str, &i)) != NULL) // TODO: norm error 
    {
        result[word_idx] = word;
        if (!result[word_idx])
        {
            free_split_array(result);
            return NULL;
        }
        word_idx++;
    }
    result[word_idx] = NULL;
    return result;
}

