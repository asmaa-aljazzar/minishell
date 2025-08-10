#include "minishell.h"
#include "minishell.h"

void copy_token_to_argvs(t_minishell *ms, t_command *cmd, t_token *tok, int arg_idx)
{
    cmd->argv[arg_idx] = ft_strdup(tok->word);
    if (!cmd->argv[arg_idx])
        ft_exit(ms, "malloc failed", EXIT_FAILURE);

    cmd->argv_expanded[arg_idx] = tok->expanded; // Direct assignment of flag (0 or 1)
}

