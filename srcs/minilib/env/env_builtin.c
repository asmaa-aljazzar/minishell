#include "minishell.h"
void env_builtin(t_minishell *minishell)
{
    t_command *cmd = minishell->cmd;

    // case: no arguments → print environment
    if (cmd->argv[1] == NULL)
    {
        t_env *curr = minishell->env;
        while (curr)
        {
            if (curr->value)
                printf("%s=%s\n", curr->name, curr->value);
            curr = curr->next;
        }
        minishell->exit_code = 0;
        return;
    }

    // Setup temporary command to resolve path of cmd->argv[1]
    t_command temp_cmd = {0};
    temp_cmd.argv = &cmd->argv[1]; // skip "env"
    t_command *original_cmd = minishell->cmd;
    minishell->cmd = &temp_cmd;

    char *path = get_path(minishell);

    minishell->cmd = original_cmd;

    pid_t pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("minishell: env: fork failed\n", STDERR_FILENO);
        free(path);
        minishell->exit_code = 1;
        return;
    }

    if (pid == 0)
    {
        setup_signals_child();

        // child: try to exec
        if (path)
            execve(path, &cmd->argv[1], minishell->envp);
        else
            execve(cmd->argv[1], &cmd->argv[1], minishell->envp);

        // If execve fails
        ft_putstr_fd("minishell: env: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);

        if (errno == EISDIR)
            ft_putstr_fd("Not a directory\n", STDERR_FILENO);
        else if (errno == ENOENT)
            ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
        else if (errno == EACCES)
            ft_putstr_fd("Permission denied\n", STDERR_FILENO);
        else
        {
            ft_putstr_fd(strerror(errno), STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }

        exit((errno == EACCES || errno == EISDIR) ? 126 : 127);
    }

    // parent: wait
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        minishell->exit_code = WEXITSTATUS(status);
    else
        minishell->exit_code = 1;

    if (path)
        free(path);
}