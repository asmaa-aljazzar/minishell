
#include "minishell.h"

int exec_builtin(t_minishell *shell)
{
        // if (is_builtin(shell->cmd) == 1)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 2)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 3)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 4)
        // {
        //     return (1);
        // }
        if (is_builtin(shell->cmd) == 5)
        {
            // cd_builtin(shell);
            return (1);
        }
        // if (is_builtin(shell->cmd) == 5)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 5)
        // {
        //     return (1);
        // }
        if ((is_builtin(shell->cmd)) == 6)
        {
            env_builtin(shell);
            return(1);
        }
        if (is_builtin(shell->cmd) == 7)
        {
            pwd_builtin(shell);
            return(1);
        }
        // if (is_builtin(shell->cmd) == 8)
        // {
        //     return(1);
        // }
    return (0);
}