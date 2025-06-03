#include "../includes/minishell.h"
// TODO:
// function to distroy tokens.

static void minishell_loop ()
{
	char *input;
	while (1)
	{
		input = readline(PROMPT);
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		if (input)
			add_history(input);
		if (input && input[0])
		{
			// parsing
			// execute
			// free and distroy
		}

	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	// handle_signals ();
	minishell_loop();
	return (0);
}

