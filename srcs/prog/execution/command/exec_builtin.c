#include "minishell.h"
//*#### Executes the builtin command based on its type.
//* Returns 1 if a builtin was executed, 0 otherwise.
//* Assumes `builtin_type` is a valid type from `is_builtin`.
int execute_builtin_by_type(int builtin_type, t_minishell *shell)
{
    if (builtin_type == 1)
        echo_builtin(shell);
    else if (builtin_type == 2)
        cd_builtin(shell);
    else if (builtin_type == 3)
        pwd_builtin(shell);
    else if (builtin_type == 4)
        export_builtin(shell);
    else if (builtin_type == 5)
        unset_builtin(shell);
    else if (builtin_type == 6)
        env_builtin(shell);
    else if (builtin_type == 7)
        exit_builtin(shell);
    else
        return 0;
    return 1;
}
//*#### Detects and executes a builtin command in the shell.
//* Returns 1 if a builtin was executed, 0 otherwise.
int exec_builtin(t_minishell *shell)
{
    int builtin_type;
    int exec_by_type;
    
    builtin_type = is_builtin(shell->cmd);
    printf("builtin type: %d\n", builtin_type);
    exec_by_type = execute_builtin_by_type(builtin_type, shell);
    return exec_by_type;
}

