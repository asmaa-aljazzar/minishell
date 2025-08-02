
#include "minishell.h"

void if_output_filesAppend(t_minishell *minishell, t_token *token, t_command **cmd, int *i)
{
    if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
    {
        if (minishell->tok[(*i) + 1])
        {
            char *file = minishell->tok[++(*i)]->word;
            if (has_more_redirections(minishell->tok, *i + 1, OUTPUT_FILE, OUTPUT_APPEND))
                (*cmd)->output_files = add_to_list((*cmd)->output_files, file);
            else
            {
                (*cmd)->output_type = token->type;
                (*cmd)->output_file = ft_strdup(file); // FIX: Duplicate this too
            }
        }
    }
}