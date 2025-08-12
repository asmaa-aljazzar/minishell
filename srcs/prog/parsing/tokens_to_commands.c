
#include "minishell.h"

void	tokens_to_commands(t_minishell *minishell)
{
	t_command	*cmd;
	t_token		*token;
	int			i;
	int			argc;

	cmd = minishell->cmd;
	i = 0;
	argc = 0;
	while (minishell->tok[i])
	{
		token = minishell->tok[i];
		if_output_pipe(token, &cmd, &argc);
		if_input_files_heredoc(minishell, token, &cmd, &i);
		if_output_files_append(minishell, token, &cmd, &i);
		if (token->type == INPUT_WORD)
			cmd->argv[argc++] = token->word;
		// pritnf("token %d = %s", i, minishell->tok[i]->word)
		i++;
	}
	if (cmd && cmd->argv)
		cmd->argv[argc] = NULL;
}
