// cd_builtin.c
#include "minishell.h"

void cd_builtin(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    char *path;
    char *oldpwd;
    char *expanded_path = NULL;
    char *display_path;  // For error messages

    // Too many arguments
    if (cmd->argv[1] && cmd->argv[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        shell->exit_code = 1;
        return;
    }

    // Save current directory
    oldpwd = getcwd(NULL, 0);

    // Determine target path
    if (!cmd->argv[1] || (ft_strncmp(cmd->argv[1], "--", 3) == 0))
    {
        path = get_env_value(shell->env, "HOME");
        display_path = "HOME";
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            shell->exit_code = 1;
            free(oldpwd);
            return;
        }
    }
    else if (cmd->argv[1][0] == '~')
    {
        char *home = get_env_value(shell->env, "HOME");
        if (!home)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
            shell->exit_code = 1;
            free(oldpwd);
            return;
        }

        if (cmd->argv[1][1] == '\0')
        {
            path = home;
            display_path = cmd->argv[1];
        }
        else if (cmd->argv[1][1] == '/')
        {
            expanded_path = ft_strjoin(home, cmd->argv[1] + 1);
            if (!expanded_path)
            {
                ft_putstr_fd("minishell: cd: memory allocation failed\n", STDERR_FILENO);
                shell->exit_code = 1;
                free(oldpwd);
                return;
            }
            path = expanded_path;
            display_path = expanded_path;
        }
        else
        {
            path = cmd->argv[1];
            display_path = cmd->argv[1];
        }
    }
    else if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
    {
        path = get_env_value(shell->env, "OLDPWD");
        display_path = "-";
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
            shell->exit_code = 1;
            free(oldpwd);
            return;
        }
        ft_putstr_fd(path, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
    {
        path = cmd->argv[1];
        display_path = cmd->argv[1];
    }

    // Try changing directory
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        ft_putstr_fd(display_path, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        if (errno == ENOENT)
            ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
        else if (errno == EACCES)
            ft_putstr_fd("Permission denied\n", STDERR_FILENO);
        else if (errno == ENOTDIR)
            ft_putstr_fd("Not a directory\n", STDERR_FILENO);
        else
        {
            ft_putstr_fd(strerror(errno), STDERR_FILENO);
            ft_putstr_fd("\n", STDERR_FILENO);
        }
        shell->exit_code = 1;
        free(oldpwd);
        if (expanded_path)
            free(expanded_path);
        return;
    }

    // Update OLDPWD
    update_env_var(shell, "OLDPWD", oldpwd);
    free(oldpwd);

    // Determine new PWD
    char *cwd = getcwd(NULL, 0);
    if (cwd)
    {
        update_env_var(shell, "PWD", cwd);
        free(cwd);
    }
    else
    {
        // If getcwd fails (e.g., directory was removed),
        // use absolute path if provided, else unset PWD
        if (path && path[0] == '/')
            update_env_var(shell, "PWD", path);
        else
            update_env_var(shell, "PWD", NULL);
    }

    shell->exit_code = 0;

    if (expanded_path)
        free(expanded_path);
}
