#include "minishell.h"

char	**init_split_array(char *str, int *word_count)
{
	char	**result;

	if (!str || !*str)
		return (NULL);
	*word_count = count_words_in_string(str);
	if (*word_count == 0)
		return (NULL);
	result = ft_calloc(*word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}
