#include "minishell.h"

int fill_argvs(t_minishell *ms)
{
    t_command *cmd = ms->cmd;
    int i = 0;
    int arg_idx = 0;
    t_token *tok;

    while (ms->tok[i])
    {
        tok = ms->tok[i];
        if (process_token_to_fill(ms, &cmd, tok, &arg_idx) == 2)
        {
            i++;
            if (ms->tok[i])
                ms->tok[i]->type = T_FILE;
            else
            {
                ft_printf("syntax error near unexpected token `newline'\n");
                ms->exit_code = 2;
                return (-1);
            }
        }
        i++;
    }
    if (cmd)
        cmd->argv[arg_idx] = NULL;
    return (0);
}
