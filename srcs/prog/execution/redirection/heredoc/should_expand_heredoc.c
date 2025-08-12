#include "minishell.h"

int should_expand_heredoc(t_minishell *shell, char *delimiter)
{
    int i;

    i = 0;
    while (shell->tok[i])
    {
        if (shell->tok[i]->word && 
            ft_strncmp(shell->tok[i]->word, delimiter, ft_strlen(delimiter)) == 0)
            return (shell->tok[i]->qtype != QUOTE_SINGLE);
        i++;
    }
    return (1);
}