// is_builtin.c
#include "minishell.h"

int is_builtin(t_command *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    
    if (ft_strncmp(cmd->argv[0], "echo", ft_strlen ("echo")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "cd", ft_strlen ("cd")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen ("pwd")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "export", ft_strlen ("export")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "unset", ft_strlen ("unset")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "env", ft_strlen ("env")) == 0)
        return 1;
    if (ft_strncmp(cmd->argv[0], "exit", ft_strlen ("exit")) == 0)
        return 1;
    
    return 0;
}