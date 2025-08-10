// compare_commands.c
#include "minishell.h"

void compare_commands(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    
    if (!cmd || !cmd->argv || !cmd->argv[0])
    {
        shell->exit_code = 0;
        return;
    }
    
    // Check if it's a builtin
    if (ft_strncmp(cmd->argv[0], "echo", ft_strlen ("echo")) == 0)
        echo_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "cd", ft_strlen ("cd")) == 0)
        cd_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen ("pwd")) == 0)
        pwd_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "export", ft_strlen ("export")) == 0)
        export_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "unset", ft_strlen ("unset")) == 0)
        unset_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "env", ft_strlen ("env")) == 0)
        env_builtin(shell);
    else if (ft_strncmp(cmd->argv[0], "exit", ft_strlen ("exit")) == 0)
        exit_builtin(shell);
    else
    {
        // External command
        execute_external_command(shell);
    }
}