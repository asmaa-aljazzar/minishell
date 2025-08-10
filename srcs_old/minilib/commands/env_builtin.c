#include "minishell.h"

void env_builtin(t_minishell *minishell)
{
    t_command *cmd = minishell->cmd;

    // Case: no arguments → print environment
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

    char *path = NULL;
    int is_direct_path = (ft_strchr(cmd->argv[1], '/') != NULL);

    if (!is_direct_path)
    {
        // Only search PATH if no slash is included in argv[1]
        t_command temp_cmd = {0};
        temp_cmd.argv = &cmd->argv[1];

        t_command *original_cmd = minishell->cmd;
        minishell->cmd = &temp_cmd;
        path = get_path(minishell);
        minishell->cmd = original_cmd;

        if (!path)
        {
            ft_putstr_fd("minishell: env: ", STDERR_FILENO);
            ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
            ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
            minishell->exit_code = 127;
            return;
        }
    }

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
        if (is_direct_path)
            execve(cmd->argv[1], &cmd->argv[1], minishell->envp);
        else
            execve(path, &cmd->argv[1], minishell->envp);

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

        // Exit code: 126 = permission/dir error, 127 = not found
        if (errno == EACCES || errno == EISDIR)
            exit(126);
        else
            exit(127);
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
