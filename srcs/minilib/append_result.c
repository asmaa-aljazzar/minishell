
#include "minishell.h"

char *append_result(char *old_result, char *value)
{
	char *temp = old_result;
	char *new_result = ft_strjoin(old_result, value);
	free(temp);
	return new_result;
}