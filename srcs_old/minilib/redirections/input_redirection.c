// input_redirection.c
#include "minishell.h"

void input_redirection(t_command *cmd)
{
    int fd;
    
    if (!cmd->input_file)
        return;
    
    fd = open(cmd->input_file, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(cmd->input_file);
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
}