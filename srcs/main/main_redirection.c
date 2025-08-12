#include "minishell.h"
int main_redirection(t_minishell *ms)
{

    t_command *cmd = ms->cmd;
    int fd;

    // //! Debug
    // // int i = 0;
    // // ft_putstr_fd("Output files in main_redirection:\n", STDERR_FILENO);
    // // while (cmd->output_files && cmd->output_files[i])
    // // {
    // //     ft_putstr_fd("  ", STDERR_FILENO);
    // //     ft_putstr_fd(cmd->output_files[i], STDERR_FILENO);
    // //     ft_putstr_fd("\n", STDERR_FILENO);
    // //     i++;
    // // }

    // ft_putstr_fd("Output type: ", STDERR_FILENO);
    // if (cmd->output_type == OUTPUT_APPEND)
    //     ft_putstr_fd("APPEND\n", STDERR_FILENO);
    // else if (cmd->output_type == OUTPUT_FILE)
    //     ft_putstr_fd("TRUNCATE\n", STDERR_FILENO);
    // else
    //     ft_putstr_fd("NONE or other\n", STDERR_FILENO);
    // //! End Debug

    if (!cmd)
        return 0;

    // Input redirection (last input file)
    if (cmd->input_files)
    {
        int i = 0;
        while (cmd->input_files[i])
            i++;
        fd = open(cmd->input_files[i - 1], O_RDONLY);
        if (fd < 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            perror(cmd->input_files[i - 1]);
            return -1;
        }
        if (dup2(fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            close(fd);
            return -1;
        }
        close(fd);
    }
    else if (cmd->input_type == INPUT_HEREDOC)
    {
        if (!setup_heredoc_input(cmd))
            return -1;
    }
    else if (cmd->input_type == INPUT_FILE)
    {
        if (input_redirection(cmd) != 0)
            return -1;
    }

    // Output redirection (create/truncate all output files, redirect last)
    if (cmd->output_files)
    {
        int i = 0;
        int last_index;

        while (cmd->output_files[i])
            i++;
        last_index = i - 1;

        for (i = 0; cmd->output_files[i]; i++)
        {
            int flags = O_WRONLY | O_CREAT;
            if (cmd->output_type == OUTPUT_APPEND)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;

            fd = open(cmd->output_files[i], flags, 0644);
            if (fd < 0)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror(cmd->output_files[i]);
                return -1;
            }
            if (i == last_index)
            {
                if (dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    close(fd);
                    return -1;
                }
            }
            close(fd);
        }
    }


    return 0;
}