
#include "minishell.h"

void init(t_minishell *ms, char **environ)
{
    ms->tok = NULL; // tokens array
    ms->input = NULL; // input string
    ms->cmd = NULL; // commands linked list
    ms->tokens_count = 0; // how many tokens in tokens array
    ms->pipe_count = 0; // how many pipe we have = how many commands - 1
    ms->exit_code = 0; // exit code for each command
    ms->skip_execution = 0; // if we don't need to execute [error or no need to handle]
    ms->envp = ft_strdup_double(environ); // Initialize the envp array
	ms->env = init_env(ms, environ); // Initialize the env linked list
	ms->in_single_quote = 0; // Initialize token position if single.
	ms->in_double_quote = 0; // Initialize token position if double.
    ft_memset(ms->buff, 0, sizeof(ms->buff));// set 0 values to the buffer
    increase_SHLVL_var(ms, ms->env); // Increase SHLVL value by 1
    ms->last_token_end = -1;
}

