#include "minishell.h"

char *read_until_delimiter(char *delimiter)
{
    char *content = ft_strdup("");
    char *line;
    int should_break;
    setup_signals_heredoc();
    while (1)
    {
        line = readline("> ");
        if (g_signal_received == SIGINT)
        {
            if (line)
                free(line);
            free(content);
            dup2(2, 0);
            return NULL; // Abort heredoc input
        }
        content = process_heredoc_readline(content, line, delimiter, &should_break);
        if (!content || should_break)
            break;
    }
    setup_signals_parent();
    return content;
}
