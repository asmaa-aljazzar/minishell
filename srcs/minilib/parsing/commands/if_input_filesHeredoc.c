
#include "minishell.h"

void if_input_filesHeredoc(t_minishell *minishell, t_token *token, t_command **cmd, int *i)
{
    if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
    {
        if (minishell->tok[(*i) + 1])
        {
            char *file = minishell->tok[++(*i)]->word;
            if (has_more_redirections(minishell->tok, *i + 1, INPUT_FILE, INPUT_HEREDOC))
                (*cmd)->input_files = add_to_list((*cmd)->input_files, file);
            else
            {
                (*cmd)->input_type = token->type;
                (*cmd)->input_file = ft_strdup(file);
            }
        }
    }
}