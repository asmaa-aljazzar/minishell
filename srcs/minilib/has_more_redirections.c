
#include "minishell.h"

int has_more_redirections(t_token **tokens, int start_index, t_type t1, t_type t2)
{
	int i = start_index;
	while (tokens[i])
	{
		printf("cond token: %s\n", tokens[i]->word);
		if (tokens[i]->type == t1 || tokens[i]->type == t2)
			return 1;
		i++;
	}
	return 0;
}
