
#include "minishell.h"

char *expand_heredoc_variables(t_minishell *shell, char *content)
{
    char *result;
    int i;

    if (!content)
        return (ft_strdup(""));
    result = ft_strdup("");
    i = 0;
    while (content[i])
    {
        if (content[i] == '$' && content[i + 1])
        {
            if (content[i + 1] == '?')
                result = expand_exit_code(shell, result, &i);
            else if (ft_isalpha(content[i + 1]) || content[i + 1] == '_')
                result = expand_env_var(shell, content, result, &i);
            else
                result = append_single_char(result, content[i++]);
        }
        else
            result = append_single_char(result, content[i++]);
    }
    return (result);
}
