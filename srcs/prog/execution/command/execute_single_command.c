#include "minishell.h"

static int open_multiple_output_files(t_command *cmd, t_minishell *ms)
{
    int i;
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
    return 0;
}

// static int open_single_output_file(t_command *cmd, t_minishell *ms)
// {
//     int flags = O_WRONLY | O_CREAT | O_TRUNC;
//     if (cmd->output_type == OUTPUT_APPEND)
//         flags = O_WRONLY | O_CREAT | O_APPEND;

//     int fd = open(cmd->output_file, flags, 0644);
//     if (fd < 0)
//     {
//         perror(cmd->output_file);
//         ms->exit_code = 1;
//         return -1;
//     }
//     close(fd);
//     return 0;
// }

static int open_output_files(t_command *cmd, t_minishell *ms)
{
    if (cmd->output_files)
        return open_multiple_output_files(cmd, ms);
    // else if (cmd->output_file)
    //     return open_single_output_file(cmd, ms);
    return 0;
}


int handle_empty_command_with_output(t_minishell *ms)
{
    t_command *cmd = ms->cmd;

    if (!cmd)
        return 0;

    if ((!cmd->argv || !cmd->argv[0] || is_command_empty(cmd)) &&
        (cmd->output_type != OUTPUT_NONE || (cmd->output_files && cmd->output_files[0])))
    {
        if (open_output_files(cmd, ms) == -1)
            return -1;
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
static int save_and_apply_redirection(t_minishell *ms, int *saved_stdout)
{
    t_command *cmd = ms->cmd;
    *saved_stdout = -1;

    if (cmd->output_type != OUTPUT_NONE || cmd->output_files)
    {
        *saved_stdout = dup(STDOUT_FILENO);
        if (*saved_stdout < 0)
        {
            perror("dup");
            ms->exit_code = 1;
            return -1;
        }
        if (main_redirection(ms) != 0)
        {
            if (*saved_stdout >= 0)
                close(*saved_stdout);
            ms->exit_code = 1;
            return -1;
        }
    }
    return 0;
}

static void execute_builtin_and_restore(t_minishell *ms, int saved_stdout)
{
    compare_commands(ms); // Execute builtin

    if (saved_stdout >= 0)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
}

static int handle_builtin_with_redirection(t_minishell *ms)
{
    int saved_stdout;

    if (save_and_apply_redirection(ms, &saved_stdout) != 0)
        return -1;

    execute_builtin_and_restore(ms, saved_stdout);

    return 0;
}


static void fork_and_execute_external(t_minishell *ms)
{
    pid_t pid = fork();
    int status;
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
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            ms->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            ms->exit_code = 128 + WTERMSIG(status);
    }
}

static int validate_command_for_execution(t_minishell *ms)
{
    t_command *cmd = ms->cmd;

    if (!cmd || !cmd->argv)
    {
        ms->exit_code = 0;
        return 0;
    }
    if (handle_empty_command_with_output(ms))
        return 0;
    if (!cmd->argv[0])
    {
        ms->exit_code = 0;
        return 0;
    }
    if (is_command_empty(cmd))
    {
        ms->exit_code = 0;
        return 0;
    }
    return 1;
}

static void handle_builtin_command(t_minishell *ms)
{
    if (handle_builtin_with_redirection(ms) != 0)
        return;
}

void execute_single_command(t_minishell *ms)
{
    if (!validate_command_for_execution(ms))
        return;

    if (is_builtin(ms->cmd))
    {
        handle_builtin_command(ms);
        return;
    }

    fork_and_execute_external(ms);
}

