#include "minishell.h"

void	free_split_array(char **array)
{
	int	i;
	
	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
