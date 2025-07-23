/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/23 18:52:27 by aaljazza         ###   ########.fr       */
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

void debug_commands(t_minishell *minishell)
{
	int cmd_num = 0;
	t_command *cmd = minishell->cmd;

	while (cmd)
	{
		printf("─── Command #%d ───\n", cmd_num);

		printf("ARGV: ");
		if (cmd->argv)
		{
			int i = 0;
			while (cmd->argv[i])
			{
				printf("[%s] ", cmd->argv[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(null)\n");

		printf("Input Type: %d\n", cmd->input_type);
		printf("Input File: %s\n", cmd->input_file ? cmd->input_file : "(null)");
		printf("Output Type: %d\n", cmd->output_type);
		printf("Output File: %s\n", cmd->output_file ? cmd->output_file : "(null)");

		printf("Next Command: %s\n\n", cmd->next ? "exists" : "NULL");

		cmd = cmd->next;
		cmd_num++;
	}
}

//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Each new prompt will initialize the rest of elements in the structure.
//* 3. Handle redirections.
//* 4. Forking.
//* 5. Free if allocated or exit.
int main(int ac, char **av, char **environ)
{
    (void)ac;
    (void)av;
    t_minishell minishell;

    init(&minishell);
    minishell.env = init_env(&minishell, environ);
    
    while (1)
    {
        init_shell(&minishell);
        
        // Skip processing if no input or no tokens
        if (!minishell.input || !minishell.tok)
        {
            continue;  // Skip to next iteration
        }
        
        // Handle exit command
        if (strcmp(minishell.input, "exit") == 0)
        {
            check_to_free(&minishell);
            free_env(minishell.env);
            rl_clear_history();
            printf("exit\n");
            exit(0);
        }
        
        // Process the command pipeline
        init_commands(&minishell);
        expand_tokens(&minishell);
        merge_words(&minishell);
        allocate_argv_for_commands(&minishell);
        tokens_to_commands(&minishell);
        debug_commands(&minishell);
        
        // Clean up for next iteration
        check_to_free(&minishell);
    }
    
    // This point should never be reached
    rl_clear_history();
    return (0);
}