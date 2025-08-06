// main_redirection.c - Updated
#include "minishell.h"

void main_redirection(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    
    if (!cmd)
        return;
    
    // Handle multiple input files (process all, but only last one matters for stdin)
    if (cmd->input_files)
    {
        int i = 0;
        while (cmd->input_files[i])
        {
            // For multiple input files, only the last one should redirect stdin
            if (cmd->input_files[i + 1] == NULL) // This is the last file
            {
                int fd = open(cmd->input_files[i], O_RDONLY);
                if (fd < 0)
                {
                    ft_putstr_fd("minishell: ", STDERR_FILENO);
                    perror(cmd->input_files[i]);
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
            i++;
        }
    }
    // Handle single input file (fallback for old logic)
    else if (cmd->input_type == INPUT_HEREDOC)
    {
        if (!setup_heredoc_input(cmd))
            exit(EXIT_FAILURE);
    }
    else if (cmd->input_type == INPUT_FILE)
    {
        input_redirection(cmd);
    }
    
    // Handle multiple output files (ALL files should be created/truncated)
    if (cmd->output_files)
    {
        int i = 0;
        while (cmd->output_files[i])
        {
            int flags = O_WRONLY | O_CREAT;
            
            // Use the output_type for the redirection mode
            if (cmd->output_type == OUTPUT_APPEND)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;
            
            int fd = open(cmd->output_files[i], flags, 0644);
            if (fd < 0)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror(cmd->output_files[i]);
                exit(EXIT_FAILURE);
            }
            
            // Only the LAST output file should redirect stdout
            if (cmd->output_files[i + 1] == NULL) // This is the last file
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
                }
            }
            close(fd);
            i++;
        }
    }
    // Handle single output file (fallback for old logic)
    else if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
    {
        handle_output_redirection(cmd);
    }
}