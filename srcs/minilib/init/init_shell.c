/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:35 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 15:33:05 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int validate_syntax(t_minishell *ms)
{
    int i = 0;

    while (ms->tok[i])
    {
        // Check for empty pipe
        if (ms->tok[i]->type == OUTPUT_PIPE)
        {
            if (i == 0 || !ms->tok[i + 1] || ms->tok[i + 1]->type == OUTPUT_PIPE)
            {
                ft_putendl_fd("syntax error near unexpected token `|'", 2);
                return 0;
            }
        }
        // Check for redirections
        else if (ms->tok[i]->type == INPUT_FILE || 
                ms->tok[i]->type == INPUT_HEREDOC || 
                ms->tok[i]->type == OUTPUT_FILE || 
                ms->tok[i]->type == OUTPUT_APPEND)
        {
            // Must have a word token after redirection
            if (!ms->tok[i + 1] || ms->tok[i + 1]->type != INUPT_WORD)  // Note: Fix the typo INUPT_WORD to INPUT_WORD in your enum
            {
                ft_putendl_fd("syntax error near unexpected token `newline'", 2);
                return 0;
            }
            i++; // Skip the filename token we just validated
        }
        i++;
    }
    return 1;
}

// 1. Display the prompt.
// 2. Read the input line into a buffer.
// 3. Add this line to the history.
// 4. Parsing the input.
// 5. Split it into tokens.
//? 6. Move it into cmd array.
// 7. After Each initialize check for Null.
// 8. exit if error occured
void init_shell(t_minishell *minishell)
{
    // Reset tokens from previous iteration
    minishell->tok = NULL;
    minishell->tokens_count = 0;
    minishell->pipe_count = 0;
    
    // Get user input with readline
    minishell->input = readline(PROMPT);
    
    // Handle EOF (Ctrl+D)
    if (!minishell->input)
    {
        printf("exit\n");
        free_env(minishell->env);
        rl_clear_history();
        exit(0);
    }

    // Add non-empty commands to history
    if (*minishell->input)
        add_history(minishell->input);

    // Skip processing for empty commands
    if (!*minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
        return;
    }

    // Tokenize the input
    get_tokens(minishell);
    if (!minishell->tok)
    {
        ft_putendl_fd("Error: Failed to tokenize input", STDERR_FILENO);
        free(minishell->input);
        minishell->input = NULL;
        return;
    }

    // Validate syntax
    if (!validate_syntax(minishell))
    {
        check_to_free(minishell);
        return;
    }

    // Handle single built-in commands (no pipes)
    if (minishell->tok[0] && minishell->tok[1] == NULL)
    {
        // env command
        if (ft_strncmp(minishell->tok[0]->word, "env", ft_strlen("env") + 1) == 0)
        {
            env_builtin(minishell);
            check_to_free(minishell);
            return;
        }
    }
    
    // Handle built-ins that can have arguments
    if (minishell->tok[0])
    {
        // export
        if (ft_strncmp(minishell->tok[0]->word, "export", ft_strlen("export") + 1) == 0)
        {
            export_builtin(minishell);
            check_to_free(minishell);
            return;
        }
        // unset
        else if (ft_strncmp(minishell->tok[0]->word, "unset", ft_strlen("unset") + 1) == 0)
        {
            unset_builtin(minishell);
            check_to_free(minishell);
            return;
        }
    }

    // Count pipes to determine number of commands
    count_pipe(minishell);
    
    // Set default exit code for this command
    minishell->exit_code = 0;
}