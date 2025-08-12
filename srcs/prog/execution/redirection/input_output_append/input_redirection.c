// input_redirection.c
#include "minishell.h"
// input_redirection.c
#include "minishell.h"

// Redirect stdin to the file specified in cmd->input_file
// Returns 0 on success, -1 on failure (does not exit)
int input_redirection(t_command *cmd)
{
    int fd;

    if (!cmd->input_file)
        return 0;

    fd = open(cmd->input_file, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(cmd->input_file);
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}
