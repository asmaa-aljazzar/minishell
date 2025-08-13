#include "minishell.h"

void process_token_to_fill(t_minishell *ms, t_command **cmd, t_token *tok, int *arg_idx)
{
    if (tok->type == PIPE)
    {
        (*cmd)->argv[*arg_idx] = NULL;
        (*cmd)->argv_expanded[*arg_idx] = 0;
        *cmd = (*cmd)->next;
        *arg_idx = 0;
    }
    else if (tok->type != INPUT_FILE && tok->type != INPUT_HEREDOC
        && tok->type != OUTPUT_FILE && tok->type != OUTPUT_APPEND)
    {
        copy_token_to_argvs(ms, *cmd, tok, *arg_idx);
        (*arg_idx)++;
    }
}