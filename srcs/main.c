#include "../includes/minishell.h"

//TODO: fix makefile
// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && i < n)
// 	{
// 		if ((unsigned char)s1[i] != (unsigned char)s2[i])
// 		{
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline(PROMPT);
		handle_exit_and_history (input);
		if (ft_strncmp(input, "exit", 4) == 0)
			break;
		add_history (input);
		if (strncmp (input, "history", 7) == 0)
		{

		}
		free (input);
	}
	return (0);
	
}
