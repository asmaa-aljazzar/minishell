#include "minishell.h"

int prepare_command_processing(t_minishell *ms)
{
	if (!ms->input || !ms->tok)
		return (-1);
	if (expand_tokens(ms) < 0)
		return (-1);
	count_pipe(ms);
	ms->cmd = create_command_list(ms, ms->pipe_count);
	merge_words(ms);
	argv_for_commands(ms);
	if (fill_argvs(ms) < 0)
	{
		//free cmd
		//free tokens
		return (-1);
	}
	tokens_to_commands(ms);
	return (0);
}


