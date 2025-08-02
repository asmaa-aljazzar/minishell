
#include "minishell.h"

void tokenize_output_redir(t_minishell *minishell, int *k, int *i)
{
	if (minishell->input[*i + 1] == '>')
		handle_output_append_redir(minishell, k, i);
	else
		handle_output_file_redir(minishell, k, i);
}
