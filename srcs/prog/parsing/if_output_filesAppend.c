
#include "minishell.h"

// Handles output redirections: OUTPUT_FILE and OUTPUT_APPEND
// void	if_output_files_append(t_minishell *minishell, t_token *token,
// 		t_command **cmd, int *i)
// {
// 	char	*file;

// 	if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
// 	{
// 		if (minishell->tok[(*i) + 1])
// 		{
// 			file = minishell->tok[++(*i)]->word;
// 			(*cmd)->output_files = add_to_list((*cmd)->output_files, file);
// 		}
// 	}
// }
