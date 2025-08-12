#include "minishell.h"

char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    char *content;

    content = read_until_delimiter(delimiter);
    if (!content)
        return (NULL);

    if (should_expand && content)
    {
        char *expanded = expand_heredoc_variables(shell, content);
        free(content);
        content = expanded;
    }
    return content;
}
