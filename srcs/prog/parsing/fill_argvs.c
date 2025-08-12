#include "minishell.h"

void	fill_argvs(t_minishell *ms)//todo norm 25 line
{
	t_command	*cmd;
	int			i;
	int			arg_idx;
	t_token		*tok;

	cmd = ms->cmd;
	i = 0;
	arg_idx = 0;
	while (ms->tok[i])
	{
		tok = ms->tok[i];
		if (tok->type == PIPE)
		{
			cmd->argv[arg_idx] = NULL;
			cmd->argv_expanded[arg_idx] = 0;
			cmd = cmd->next;
			arg_idx = 0;
			i++;
			continue ;
		}
		if (tok->type != INPUT_FILE && tok->type != INPUT_HEREDOC
			&& tok->type != OUTPUT_FILE && tok->type != OUTPUT_APPEND)
		{
			copy_token_to_argvs(ms, cmd, tok, arg_idx);
			arg_idx++;
		}
		i++;
	}
	if (cmd)
	{
		cmd->argv[arg_idx] = NULL;
		cmd->argv_expanded[arg_idx] = 0; // Optional, no sentinel needed
	}
}
