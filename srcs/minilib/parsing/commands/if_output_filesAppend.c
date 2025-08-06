
#include "minishell.h"
void if_output_filesAppend(t_minishell *minishell, t_token *token, t_command **cmd, int *i)
{
    if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
    {
        if (minishell->tok[(*i) + 1])
        {
            char *file = minishell->tok[++(*i)]->word;
            
            // ALWAYS add to output_files array
            (*cmd)->output_files = add_to_list((*cmd)->output_files, file);
            
            // ALSO set output_type and output_file (for the last/current redirection)
            (*cmd)->output_type = token->type;
            if ((*cmd)->output_file)
                free((*cmd)->output_file);  // Free previous if exists
            (*cmd)->output_file = ft_strdup(file);
        }
    }
}