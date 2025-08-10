#include "minishell.h"

char *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break)
{
    *should_break = 0;
    if (g_signal_received == SIG_INT)
    {
        if (line)
            free(line);
        free(content);
        return (NULL);
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
