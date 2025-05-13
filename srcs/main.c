#include "../includes/minishell.h"

static void minishell_loop (t_cmd *cmd)
{
	char *input;
	int i;
	while (1)
	{
		input = readline(PROMPT);
		if (!input) // Ctrl+D
			return ;
		// if (is_valid_input(input)) // TODO
		// {
		// 	add_history(input);
		parse_and_execute(input, cmd); // TODO
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("Token[ %d ]: %s\n", i + 1, cmd->args[i]);
			i++;
		}
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free (cmd->args[i]);
			i++;
		}
		free (cmd->args);
		cmd->args = NULL;
		// }
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_cmd cmd;
	// init_envp(envp); //TODO to init env list, etc.
	init_cmd (&cmd);
	minishell_loop(&cmd);
	// cleanup_minishell(); // TODO Optional cleanup if needed
	return (0);
}