#include "minishell.h"

int process_token_to_fill(t_minishell *ms, t_command **cmd, t_token *tok, int *arg_idx)
{
    if (tok->type == PIPE)
    {
        (*cmd)->argv[*arg_idx] = NULL;
        (*cmd)->argv_expanded[*arg_idx] = 0;
        *cmd = (*cmd)->next;
        *arg_idx = 0;
		return (1); // Indicate that we moved to the next command
    }
	if (tok->type == T_INPUT || tok->type == T_HEREDOC 
		|| tok->type == T_OUTPUT || tok->type == T_APPEND)
		return (2); // Indicate that we are processing a redirection
    else if (tok->type == T_WORD)
    {
        copy_token_to_argvs(ms, *cmd, tok, *arg_idx);
        (*arg_idx)++;
		return (0);
    }
	return (3); // Indicate that we are processing a different type of token
}
