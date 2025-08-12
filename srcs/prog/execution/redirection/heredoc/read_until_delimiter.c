#include "minishell.h"

char *read_until_delimiter(char *delimiter)
{
    char *content = ft_strdup("");
    char *line;
    int should_break;
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(content);
            return NULL;
        }
        if (g_signal_received == SIGINT)
        {
            free(line);
            free(content);
            g_signal_received = 0;
            return NULL; // Abort heredoc input
        }

        content = process_heredoc_readline(content, line, delimiter, &should_break);
        if (!content || should_break)
            break;
    }
    g_signal_received = 0;
    return content;
}
