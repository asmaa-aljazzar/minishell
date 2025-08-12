#include "minishell.h"

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
    t_command *cmd = ms->cmd;// command list
    if (!cmd || !cmd->argv || !cmd->argv[0]) // check empty
    {
        ms->exit_code = 0; // empty command, do nothing
        return;
    }
    if (is_command_empty(cmd))
    {
        ms->exit_code = 0; // command is only whitespace, or $notExist do nothing
        return;
    }
    if (main_redirection(ms) != 0) // todo
    {
        ms->exit_code = 1; // redirection error
        return;
    }
    //todo
    if (is_builtin(cmd)) // If it's a builtin command, run it directly without forking
    {
        compare_commands(ms); // executes builtin, sets ms->exit_code // todo
        return;
    }
    pid_t pid = fork();// For external commands, fork and exec
    if (pid < 0)
    {
        perror("fork");
        ms->exit_code = 1;
        return;
    }
    else if (pid == 0)
    {
        setup_signals_child();// Child process
        compare_commands(ms); // runs execve for external command //todo
        exit(EXIT_FAILURE); // execve failed if reached here
    }
    else // Parent process waits for child
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            ms->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            ms->exit_code = 128 + WTERMSIG(status);
    }
}
