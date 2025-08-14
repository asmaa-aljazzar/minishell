#include "minishell.h"

//*#### Prints environment variables when no arguments to env command
void env_builtin_print_env(t_minishell *minishell)
{
    t_env *curr = minishell->env;
    while (curr)
    {
        if (curr->value)
            printf("%s=%s\n", curr->name, curr->value);
        curr = curr->next;
    }
    minishell->exit_code = 0;
}

//*#### Attempts to get executable path based on argument
// Returns allocated path string or NULL on failure
char *env_builtin_resolve_path(t_minishell *minishell, t_command *cmd)
{
    char *path = NULL;
    int is_direct_path = (ft_strchr(cmd->argv[1], '/') != NULL);
    if (!is_direct_path)
    {
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
        }
    }
    return path;
}

//*#### Executes command in a child process, handles execve errors and exit codes
void env_builtin_execute_child(t_minishell *minishell, t_command *cmd, char *path)
{
    // struct stat st;
    setup_signals_child();
    int is_direct_path = (ft_strchr(cmd->argv[1], '/') != NULL);
    if (is_direct_path)
        execve(cmd->argv[1], &cmd->argv[1], minishell->envp);
    else
        execve(path, &cmd->argv[1], minishell->envp);
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
    if (errno == EACCES || errno == EISDIR)
        exit(127);
    else
        exit(126);
}

//*#### Parent process waits for child and sets exit_code
void env_builtin_wait_child(t_minishell *minishell, pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        minishell->exit_code = WEXITSTATUS(status);
    else
        minishell->exit_code = 1;
}

//*#### Main env builtin function orchestrating helpers
void env_builtin(t_minishell *minishell)
{
    if (minishell->cmd->argv[1] == NULL)
    {
        env_builtin_print_env(minishell);
        return;
    }
    char *path = env_builtin_resolve_path(minishell, minishell->cmd);
    if (!path && minishell->exit_code == 127)
        return;
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
        env_builtin_execute_child(minishell, minishell->cmd, path);
    }
    else
    {
        env_builtin_wait_child(minishell, pid);
    }
    free(path);
}
