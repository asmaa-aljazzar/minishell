/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 15:32:23 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void allocate_argv_for_commands(t_minishell *minishell)
{
	t_command *cmd = minishell->cmd;
	int i = 0;
	int argc = 0;

	while (minishell->tok[i])
	{
		if (ft_strncmp(minishell->tok[i]->word, "|", 1) == 0)
		{
			// allocate argv for current cmd (+1 for NULL)
			cmd->argv = malloc(sizeof(char *) * (argc + 1));
			if (!cmd->argv)
				ft_exit(minishell, "malloc failed", EXIT_FAILURE);
			argc = 0;
			cmd = cmd->next;
		}
		else if (minishell->tok[i]->type != INPUT_FILE && minishell->tok[i]->type != INPUT_HEREDOC && minishell->tok[i]->type != OUTPUT_FILE && minishell->tok[i]->type != OUTPUT_APPEND)
		{
			argc++;
		}
		i++;
	}
	// last command
	if (cmd)
	{
		cmd->argv = malloc(sizeof(char *) * (argc + 1));
		if (!cmd->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
	}
}





//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Enter an infinite loop to display prompts.
//* 3. Clear the history if the loop has been broken.
int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_minishell minishell;

	init(&minishell);
	minishell.env = init_env(&minishell, environ);
	main_loop(&minishell);
	rl_clear_history();
	return (0);
}