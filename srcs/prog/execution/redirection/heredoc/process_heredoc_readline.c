#include "minishell.h"

char *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break)
{
    *should_break = 0;
    // if (g_signal_received == SIG_INT)
    if (g_signal_received == SIGINT)
    {
        if (line)
            free(line);
        free(content);
        g_signal_received = 0; // reset signal
        return NULL;           // cause readline loop to exit
    }
    if (!line)
    {
        print_eof_warning(delimiter);
        *should_break = 1;
        return (content);
    }
    if (is_delimiter_line(line, delimiter))
    {
        free(line);
        *should_break = 1;
        return (content);
    }
    content = append_line_to_content(content, line);
    free(line);
    return (content);
}
