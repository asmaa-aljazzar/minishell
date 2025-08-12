
#include "minishell.h"

// Handles input redirections: INPUT_FILE and INPUT_HEREDOC
void	if_input_files_heredoc(t_minishell *minishell, t_token *token,
		t_command **cmd, int *i)//todo norm name func error
{
	char	*file;

	if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
	{
		if (minishell->tok[(*i) + 1])
		{
			file = minishell->tok[++(*i)]->word;
			// If more input redirections ahead, add current to input_files list
			if (has_more_redirections(minishell->tok, *i + 1, INPUT_FILE,
					INPUT_HEREDOC))
			{
				(*cmd)->input_files = add_to_list((*cmd)->input_files, file);
			}
			else
			{
				// Last input redirection: set input_type and input_file
				(*cmd)->input_type = token->type;
				if ((*cmd)->input_file)
					free((*cmd)->input_file);
				(*cmd)->input_file = ft_strdup(file);
			}
		}
	}
}

