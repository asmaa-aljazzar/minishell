
#include "minishell.h"

void ft_exit(t_minishell *minishell, char *str, int status)
{
    if (str && *str)
        ft_putendl_fd(str, STDERR_FILENO);
    if (minishell->cmd)
    {
        free_commands(minishell);
        minishell->cmd = NULL;
    }
    if (minishell->tok)
    {
        free_tokens(minishell->tok);
        minishell->tok = NULL;
    }
    if (minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
    }
    if (minishell->env)
    {
        free_env(minishell->env);
        minishell->env = NULL;
    }
    if (minishell->envp)
    {
        free_2d(minishell->envp);
        minishell->envp = NULL;
    }
    rl_clear_history();
    minishell->exit_code = status;
    exit(status);
}
