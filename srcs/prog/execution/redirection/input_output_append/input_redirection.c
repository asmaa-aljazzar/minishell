// input_redirection.c
#include "minishell.h"
int input_redirection(t_command *cmd)
{
    // int fd;

    // if (!cmd || !cmd->input_file)
    //     return 0; // No input redirection needed

    // fd = open(cmd->input_file, O_RDONLY);
    // if (fd < 0)
    // {
    //     ft_putstr_fd("minishell: ", STDERR_FILENO);
    //     perror(cmd->input_file);
    //     return -1;
    // }

    (void)cmd;
    // if (dup2(fd, STDIN_FILENO) < 0)
    // {
    //     perror("dup2");
    //     close(fd);
    //     return -1;
    // }

    // close(fd);
    return 0;
}