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

    // Reject empty command: "", ''
    if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
    {
        ft_putstr_fd("minishell: ''", STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        shell->exit_code = 127;
        exit(127);
    }

    // If command contains '/', treat it as path
    if (ft_strchr(cmd->argv[0], '/'))
        cmd_path = cmd->argv[0];
    else
        cmd_path = get_path(shell); // Search in PATH

    if (!cmd_path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        shell->exit_code = 127;
        exit (127);
    }

    // Check if path is a directory
    if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        shell->exit_code = 126;
        exit (126);
        // return;
    }

    // Execute the command
    execve(cmd_path, cmd->argv, shell->envp);

    // If execve fails
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(cmd->argv[0]);

    if (errno == EACCES)
        exit(126); // Permission denied
    exit(127);     // Command not found or other errors
}