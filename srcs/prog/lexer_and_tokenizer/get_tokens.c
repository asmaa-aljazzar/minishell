
#include "minishell.h"

int	get_tokens(t_minishell *ms)
{
	size_t	len;
	int		i;
	int		k;

	len = ft_strlen(ms->input);
	i = 0;
	k = 0;
	ms->tok = ft_calloc(len + 1, sizeof(t_token *));
	if (!ms->tok)
		ft_exit(ms, "malloc failed", 1);
	ms->in_single_quote = 0;
	ms->in_double_quote = 0;
	while (ms->input[i])
	{
		while (ms->input[i] == ' ')
			i++;
		if (!ms->input[i])
			break ;
		if (!process_token(ms, &k, &i))
			return (0); // stop tokenizing on error
	}
	ms->tok[k] = NULL;
	ms->tokens_count = k;
	return (1); // success
}
