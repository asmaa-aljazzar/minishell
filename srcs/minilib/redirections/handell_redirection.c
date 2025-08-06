// handell_redirection.c - Fixed version
#include "minishell.h"

int handle_redirection(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    
    while (cmd)
    {
        // Process multiple input files (only last one matters)
        if (cmd->input_files)
        {
            int i = 0;
            while (cmd->input_files[i])
            {
                int fd = open(cmd->input_files[i], O_RDONLY);
                if (fd < 0)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    perror(cmd->input_files[i]);
                    return 0;
                }
                close(fd);
                i++;
            }
        }
        
        // Process multiple output files
        if (cmd->output_files)
        {
            int i = 0;
            while (cmd->output_files[i])
            {
                int fd = open(cmd->output_files[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    perror(cmd->output_files[i]);
                    return 0;
                }
                close(fd);
                i++;
            }
        }
        
        cmd = cmd->next;
    }
    return 1;
}