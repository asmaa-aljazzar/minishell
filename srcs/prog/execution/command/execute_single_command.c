#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int handle_empty_command_with_output(t_minishell *ms)
{
    t_command *cmd = ms->cmd;
    int i;

    if (!cmd)
        return 0;

    if ((!cmd->argv || !cmd->argv[0] || is_command_empty(cmd)) &&
        (cmd->output_type != OUTPUT_NONE || (cmd->output_files && cmd->output_files[0])))
    {
        if (cmd->output_files)
        {
            int last_index = 0;
            while (cmd->output_files[last_index])
                last_index++;
            last_index--; // last valid index

            for (i = 0; cmd->output_files[i]; i++)
            {
                int flags = O_WRONLY | O_CREAT | O_TRUNC;
                if (i == last_index && cmd->output_type == OUTPUT_APPEND)
                    flags = O_WRONLY | O_CREAT | O_APPEND;

                int fd = open(cmd->output_files[i], flags, 0644);
                if (fd < 0)
                {
                    perror(cmd->output_files[i]);
                    ms->exit_code = 1;
                    return -1;
                }
                close(fd);
            }
        }
        else if (cmd->output_file)
        {
            int flags = O_WRONLY | O_CREAT | O_TRUNC;
            if (cmd->output_type == OUTPUT_APPEND)
                flags = O_WRONLY | O_CREAT | O_APPEND;

            int fd = open(cmd->output_file, flags, 0644);
            if (fd < 0)
            {
                perror(cmd->output_file);
                ms->exit_code = 1;
                return -1;
            }
            close(fd);
        }
        ms->exit_code = 0;
        return 1;
    }
    return 0;
}


int is_command_empty(t_command *cmd)
{
    if (!cmd || !cmd->argv)
        return 1;
    char *arg = cmd->argv[0];
    while (*arg && (*arg == ' ' || *arg == '\t' || *arg == '\n'))
        arg++;
    if (*arg == '\0')
    {
        // If expanded is non-null (means result of expansion), treat as empty (skip)
        if (cmd->argv_expanded && cmd->argv_expanded[0])
            return 1; // expanded empty string → treat as empty (skip)
        // Otherwise unexpanded empty string (literal "") → treat as non-empty (execute)
        return 0;
    }
    return 0;
}
void execute_single_command(t_minishell *ms)
{
    t_command *cmd = ms->cmd;
    pid_t pid;
    int status;
    int saved_stdout = -1;

// int i = 0;

// ft_putstr_fd("Output files before handle_empty_command_with_output:\n", STDERR_FILENO);
// while (cmd->output_files && cmd->output_files[i])
// {
//     ft_putstr_fd("  ", STDERR_FILENO);
//     ft_putstr_fd(cmd->output_files[i], STDERR_FILENO);
//     ft_putstr_fd("\n", STDERR_FILENO);
//     i++;
// }

    if (!cmd || !cmd->argv)
    {
        ms->exit_code = 0;
        return;
    }
    
    if (handle_empty_command_with_output(ms))
        return;

    if (!cmd->argv[0])
    {
        ms->exit_code = 0;
        return;
    }

    if (is_command_empty(cmd))
    {
        ms->exit_code = 0;
        return;
    }

    if (is_builtin(cmd))
    {
        // Save stdout if redirection required
        if (cmd->output_type != OUTPUT_NONE || cmd->output_files)
        {
            saved_stdout = dup(STDOUT_FILENO);
            if (saved_stdout < 0)
            {
                perror("dup");
                ms->exit_code = 1;
                return;
            }
            if (main_redirection(ms) != 0)
            {
                if (saved_stdout >= 0)
                    close(saved_stdout);
                ms->exit_code = 1;
                return;
            }
        }

        compare_commands(ms); // execute builtin in parent

        // Restore stdout if redirected
        if (saved_stdout >= 0)
        {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }

        return;
    }

    // For external commands: fork and apply redirection inside child
    
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        ms->exit_code = 1;
        return;
    }
    else if (pid == 0)
    {
        setup_signals_child();
        if (main_redirection(ms) != 0)
        exit(EXIT_FAILURE);
        execute_external_command(ms);
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
        signal(SIGQUIT, handlequit);
        signal(SIGINT, handle_c);
        // fprintf(stderr, "h");
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            ms->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
        {
            ms->exit_code = 128 + WTERMSIG(status);
            if (WTERMSIG(status) == SIG_QUIT)
                write(2, "Quit (core dumped)\n", 18);
        }
        setup_signals_parent();
    }
}
