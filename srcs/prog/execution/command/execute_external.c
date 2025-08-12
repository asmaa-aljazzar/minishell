// execute_external_command.c
#include "minishell.h"
//*#### Execute external command
// • Handle absolute/relative paths
// • Reject execution of directories
// • Print clear error messages for invalid commands
void execute_external_command(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    char *cmd_path;
    struct stat st;

    if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
    {
        ft_putstr_fd("minishell: ''", STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        shell->exit_code = 127;
        exit(127);
    }

    if (ft_strcmp(cmd->argv[0], ".") == 0)
    {
        ft_putstr_fd("minishell: .: filename argument required\n", STDERR_FILENO);
        ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
        shell->exit_code = 2;
        exit(2);
    }
    else if (ft_strcmp(cmd->argv[0], "..") == 0)
    {
        ft_putstr_fd("minishell: ..: command not found\n", STDERR_FILENO);
        shell->exit_code = 127;
        exit(127);
    }

    if (ft_strchr(cmd->argv[0], '/'))
        cmd_path = cmd->argv[0];
    else
        cmd_path = get_path(shell);

    if (!cmd_path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        shell->exit_code = 127;
        exit(127);
    }

    // Check for ending slash with non-directory target
    if (cmd->argv[0][ft_strlen(cmd->argv[0]) - 1] == '/')
    {
        if (stat(cmd->argv[0], &st) != 0 || !S_ISDIR(st.st_mode))
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
            ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
            shell->exit_code = 126;
            exit(126);
        }
    }

    if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        shell->exit_code = 126;
        exit(126);
    }

    execve(cmd_path, cmd->argv, shell->envp);

    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(cmd->argv[0]);

    if (errno == EACCES)
        exit(126);
    exit(127);
}
