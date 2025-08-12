#include "minishell.h"

void fill_argvs(t_minishell *ms)
{
    t_command *cmd = ms->cmd;
    int i = 0;
    int arg_idx = 0;
    t_token *tok;

    while (ms->tok[i])
    {
        tok = ms->tok[i];
        process_token_to_fill(ms, &cmd, tok, &arg_idx);
        i++;
    }
    if (cmd)
    {
        cmd->argv[arg_idx] = NULL;
        // cmd->argv_expanded[arg_idx] = 0;
    }
}
