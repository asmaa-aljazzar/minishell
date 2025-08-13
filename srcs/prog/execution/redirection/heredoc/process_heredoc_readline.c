#include "minishell.h"

int process_heredoc_readline(int fd, char *line, char *delimiter)
{
	if (g_signal_received == SIGINT)
	{
		if (line)
			free(line);
		g_signal_received = 0; // reset signal
		return (-1);           // cause readline loop to exit
	}
	if (!line)
	{
		print_eof_warning(delimiter);
		return (-1);
	}
    if (is_delimiter_line(line, delimiter))
    {
        free(line);
        return (-1);
    }
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
    free(line);
    return (0);
}
