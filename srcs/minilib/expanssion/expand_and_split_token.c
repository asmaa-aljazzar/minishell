#include "minishell.h"

void expand_and_split_token(t_minishell *ms, t_token *token, 
                           t_token **new_tokens, int *new_count)
{
    if (token->qtype == QUOTE_SINGLE)
    {
        // No expansion in single quotes - copy as is
        new_tokens[(*new_count)++] = token;
        return;
    }
    
    // Expand the token
    char *expanded = expand_variable(ms, token->word);
    if (!expanded)
        ft_exit(ms, "Memory allocation failure during expansion", 1);
    
    if (token->qtype == QUOTE_DOUBLE)
    {
        // Double quotes: expand but don't split
        free(token->word);
        token->word = expanded;
        new_tokens[(*new_count)++] = token;
    }
    else
    {
        // Unquoted: expand AND split on whitespace
        char **split_words = split_on_whitespace(expanded);
        
        if (!split_words || !split_words[0])
        {
            // Empty expansion - create empty token
            free(token->word);
            token->word = ft_strdup("");
            new_tokens[(*new_count)++] = token;
        }
        else
        {
            // Create tokens for each split word
            int j = 0;
            while (split_words[j])
            {
                if (j == 0)
                {
                    // Reuse original token for first word
                    free(token->word);
                    token->word = ft_strdup(split_words[j]);
                    token->qtype = QUOTE_NONE; // Clear quote type after expansion
                    new_tokens[(*new_count)++] = token;
                }
                else
                {
                    // Create new tokens for additional words
                    t_token *new_token = ft_calloc(1, sizeof(t_token));
                    if (!new_token)
                        ft_exit(ms, "Memory allocation failed", 1);
                    
                    new_token->word = ft_strdup(split_words[j]);
                    new_token->type = INPUT_WORD;
                    new_token->qtype = QUOTE_NONE;
                    new_token->glued = 0; // Split tokens are not glued
                    
                    new_tokens[(*new_count)++] = new_token;
                }
                j++;
            }
        }
        
        free_split_array(split_words);
        free(expanded);
    }
}