
#include "minishell.h"

// Handles input redirections: INPUT_FILE and INPUT_HEREDOC
void	if_input_filesHeredoc(t_minishell *minishell, t_token *token,
		t_command **cmd, int *i)//todo norm name func error
{
	char	*file;

	if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
	{
		if (minishell->tok[(*i) + 1])
		{
			file = minishell->tok[++(*i)]->word;
			(*cmd)->input_files = add_to_list((*cmd)->input_files, file);
		}
	}
}

