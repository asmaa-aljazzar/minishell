#include "minishell.h"

char *extract_word_with_space(char *str, int *index)
{
    int i;
    i = *index;
    // Skip leading whitespace
    if (!str[i])
        return NULL;
    int start = *index;
    // Find end of word
    while (str[i])
        i++;
    *index = i;
    return ft_substr(str, start, i - start);
}

char **split_without_whitespace (char *str)
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
    while ((word = extract_word_with_space(str, &i)) != NULL) // TODO: norm error 
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

void handle_unquoted_token(t_minishell *ms, t_token *token, char *expanded,
                          t_token_out *out, int did_expand)//todo 5 param
{
    char **split_words;
    int j;
    if (token->glued == 1)
        split_words = split_without_whitespace (expanded);
    else
        split_words = split_on_whitespace(expanded);
    if (!split_words || !split_words[0])
    {
        free(token->word);
        token->word = ft_strdup("");
        token->expanded = did_expand;
        out->new_tokens[(*out->new_count)++] = token;
    }
    else
    {
        j = 0;
        while (split_words[j])
        {
            if (j == 0)
                handle_first_split_token(token, split_words[j], did_expand, out);
            else
                out->new_tokens[(*out->new_count)++] = create_new_token(ms,
                    split_words[j], did_expand);
            j++;
        }
    }
    free_split_array(split_words);
    free(expanded);
}
