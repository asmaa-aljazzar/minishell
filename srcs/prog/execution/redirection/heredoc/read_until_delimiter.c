#include "minishell.h"

char *read_until_delimiter(char *delimiter)
{
    char *content;
    char *line;
    int should_break;
    
    content = ft_strdup("");
    while (1)
    {
        line = readline("> ");
        content = process_heredoc_readline(content, line, delimiter, &should_break);
        
        if (!content || should_break)
            break;
    }
    return (content);
}