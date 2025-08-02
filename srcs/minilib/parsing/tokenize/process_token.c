
#include "minishell.h"

void process_token(t_minishell *minishell, int *k, int *i)
{
	int glued;
	
	glued = 1;
	if (minishell->input[*i] == ' ')
	{
		glued = 0;
		while (minishell->input[*i] == ' ')
			(*i)++;
	}
	if (!minishell->input[*i])
		return;
	if (*k == 0)
		glued = 0;
	if (minishell->input[*i] == '|')
		tokenize_pipe_op(minishell, k, i);
	else if (minishell->input[*i] == '<' || minishell->input[*i] == '>')
		tokenize_input_redir(minishell, k, i);
	else
		tokenize_quoted(minishell, k, i, glued);
}
