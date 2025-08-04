#include "minishell.h"

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int count_words_in_string(char *str)
{
    int count = 0;
    int in_word = 0;
    int i = 0;
    
    if (!str)
        return 0;
        
    while (str[i])
    {
        if (!is_whitespace(str[i]))
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
        }
        else
        {
            in_word = 0;
        }
        i++;
    }
    return count;
}

char **split_on_whitespace(char *str)
{
    if (!str || !*str)
        return NULL;
    
    int word_count = count_words_in_string(str);
    if (word_count == 0)
        return NULL;
    
    char **result = ft_calloc(word_count + 1, sizeof(char *));
    if (!result)
        return NULL;
    
    int i = 0, word_idx = 0;
    while (str[i])
    {
        // Skip whitespace
        while (str[i] && is_whitespace(str[i]))
            i++;
        
        if (str[i])
        {
            int start = i;
            // Find end of word
            while (str[i] && !is_whitespace(str[i]))
                i++;
            
            // Extract word
            result[word_idx] = ft_substr(str, start, i - start);
            if (!result[word_idx])
            {
                free_split_array(result);
                return NULL;
            }
            word_idx++;
        }
    }
    result[word_idx] = NULL;
    return result;
}

void free_split_array(char **array)
{
    if (!array)
        return;
    
    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}