
#include "minishell.h"

void if_outputPipe(t_token *token, t_command **cmd, int *argc)
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