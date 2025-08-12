
#include "minishell.h"

void	if_output_pipe(t_token *token, t_command **cmd, int *argc) //todo norm name func error
{
	if (token->type == PIPE)
	{
		if (*cmd && (*cmd)->argv)
			(*cmd)->argv[*argc] = NULL;
		if (*cmd)
			*cmd = (*cmd)->next;
		*argc = 0;
	}
}
