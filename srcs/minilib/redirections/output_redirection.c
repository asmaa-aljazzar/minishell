// output_redirection.c
#include "minishell.h"

void handle_output_redirection(t_command *cmd)
{
    int fd;
    int flags;
    
    if (!cmd->output_file)
        return;
    
    if (cmd->output_type == OUTPUT_APPEND)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    
    fd = open(cmd->output_file, flags, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(cmd->output_file);
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
}