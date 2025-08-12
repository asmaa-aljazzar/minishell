
#include "minishell.h"

// Handles output redirections: OUTPUT_FILE and OUTPUT_APPEND
void	if_output_files_append(t_minishell *minishell, t_token *token,
		t_command **cmd, int *i)
{
	char	*file;

	if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
	{
		if (minishell->tok[(*i) + 1])
		{
			file = minishell->tok[++(*i)]->word;
			// If more output redirections ahead,add current to output_files list
			if (has_more_redirections(minishell->tok, *i + 1, OUTPUT_FILE,
					OUTPUT_APPEND))
			{
				(*cmd)->output_files = add_to_list((*cmd)->output_files, file);
			}
			else
			{
				// Last output redirection: set output_type and output_file
				(*cmd)->output_type = token->type;
				if ((*cmd)->output_file)
					free((*cmd)->output_file);
				(*cmd)->output_file = ft_strdup(file);
			}
		}
	}
}
