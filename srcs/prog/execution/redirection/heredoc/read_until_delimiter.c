#include "minishell.h"

int read_until_delimiter(t_minishell *shell, char *delimiter, 
		int fd, int should_expand)
{
    char *line;
	char *expanded;

    while (1)
    {
        line = readline("> ");
        if (g_signal_received == SIGINT)
        {
            // fprintf(stderr, "%d\n", (g_signal_received == SIGINT));
            free(line);
            dup2(2, 0);
            return  -1; // Abort heredoc input
         }
        if (!line)
            return (-1);
		if (should_expand)
    	{
        	expanded = expand_heredoc_variables(shell, line);
        	free(line);
        	line = expanded;
    	}
        if (process_heredoc_readline(fd, line, delimiter) == -1)
			break; // Exit loop if delimiter is reached or EOF
    }
    // g_signal_received = 0;
    return (0);
}