
#include "minishell.h"

void free_complex_resources(t_minishell *shell)
{
    if (shell->cmd)
    {
        free_commands(shell); // commands linked list
        shell->cmd = NULL;
    }
    if (shell->tok)
    {
        free_tokens(shell->tok); // tokens array
        shell->tok = NULL;
    }
    if (shell->env)
    {
        free_env(shell->env); // env linked list
        shell->env = NULL;
    }
    if (shell->envp)
    {
        free_2d(shell->envp); // envp array
        shell->envp = NULL;
    }
}
