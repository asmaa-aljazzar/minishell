#include "minishell.h"

int exec_builtin(t_minishell *shell)
{
    int builtin_type = is_builtin(shell->cmd);
    
    if (builtin_type == 1)
    {
        echo_builtin(shell);
        return 1;
    }
    if (builtin_type == 2)
    {
        cd_builtin(shell);
        return 1;
    }
    if (builtin_type == 3)
    {
        pwd_builtin(shell);
        return 1;
    }
    if (builtin_type == 4)
    {
        export_builtin(shell);
        return 1;
    }
    if (builtin_type == 5)
    {
        unset_builtin(shell);
        return 1;
    }
    if (builtin_type == 6)
    {
        env_builtin(shell);
        return 1;
    }
    if (builtin_type == 7)
    {
        exit_builtin(shell);
        return 1;
    }
    
    return 0;
}