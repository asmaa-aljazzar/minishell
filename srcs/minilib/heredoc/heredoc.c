/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:41:35 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/29 11:05:35 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global for signal handling
extern int g_signal_received;

// Expand variables in heredoc content ($VAR and $?)
char *expand_heredoc_variables(t_minishell *shell, char *content)
{
    char *result;
    char *temp;
    char *itoa_result;
    int i;

    if (!content)
        return (ft_strdup(""));

    result = ft_strdup("");
    i = 0;

    while (content[i])
    {
        if (content[i] == '$' && content[i + 1])
        {
            if (content[i + 1] == '?')
            {
                // Handle $? (exit status)
                itoa_result = ft_itoa(shell->exit_code);
                temp = result;
                result = ft_strjoin(result, itoa_result);
                free(temp);
                free(itoa_result);
                i += 2;
            }
            else if (ft_isalpha(content[i + 1]) || content[i + 1] == '_')
            {
                // Handle $VAR (environment variable)
                char var_name[256];
                int j = 0;
                i++; // Skip $

                while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
                    var_name[j++] = content[i++];
                var_name[j] = '\0';

                char *var_value = get_env_value(shell->env, var_name);
                temp = result;
                result = ft_strjoin(result, var_value ? var_value : "");
                free(temp);
            }
            else
            {
                // Just $ followed by non-variable char
                char c[2] = {content[i], '\0'};
                temp = result;
                result = ft_strjoin(result, c);
                free(temp);
                i++;
            }
        }
        else
        {
            // Regular character
            char c[2] = {content[i], '\0'};
            temp = result;
            result = ft_strjoin(result, c);
            free(temp);
            i++;
        }
    }

    return (result);
}

// Read heredoc content until delimiter is found
char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    char *content;
    char *line;
    char *temp;
    char *expanded;

    content = ft_strdup("");
    g_signal_received = SIG_NONE;

    while (1)
    {
        line = readline("> ");

        // Handle Ctrl+C
        if (g_signal_received == SIG_INT)
        {
            if (line)
                free(line);
            free(content);
            return (NULL);
        }

        // Handle Ctrl+D (EOF)
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putendl_fd("')", 2);
            break;
        }

        // Check if line matches delimiter exactly
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }

        // Add line to content with newline
        temp = content;
        content = ft_strjoin(content, line);
        free(temp);
        temp = content;
        content = ft_strjoin(content, "\n");
        free(temp);
        free(line);
    }

    // Expand variables if needed
    if (should_expand && content)
    {
        expanded = expand_heredoc_variables(shell, content);
        free(content);
        content = expanded;
    }

    return (content);
}

// Create pipe with heredoc content for command execution
int create_heredoc_pipe(char *content)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
        return (-1);

    // Write content to pipe (even if empty)
    if (content && ft_strlen(content) > 0)
    {
        if (write(pipefd[1], content, ft_strlen(content)) == -1)
        {
            close(pipefd[0]);
            close(pipefd[1]);
            return (-1);
        }
    }

    close(pipefd[1]);   // Close write end
    return (pipefd[0]); // Return read end
}

// Check if delimiter should expand variables (not single-quoted)
int should_expand_heredoc(t_minishell *shell, char *delimiter)
{
    int i;

    i = 0;
    // Find the token with this delimiter to check its quote type
    while (shell->tok[i])
    {
        if (shell->tok[i]->word && ft_strncmp(shell->tok[i]->word, delimiter, ft_strlen(delimiter)) == 0)
        {
            return (shell->tok[i]->qtype != QUOTE_SINGLE);
        }
        i++;
    }
    return (1); // Default: expand variables
}

// Setup heredoc input for command execution
int setup_heredoc_input(t_command *cmd)
{
    int heredoc_fd;

    if (cmd->input_type != INPUT_HEREDOC || !cmd->input_file)
        return (0);

    // cmd->input_file now contains the heredoc content
    heredoc_fd = create_heredoc_pipe(cmd->input_file);
    if (heredoc_fd >= 0)
    {
        if (dup2(heredoc_fd, STDIN_FILENO) == -1)
        {
            close(heredoc_fd);
            return (0);
        }
        close(heredoc_fd);
        return (1);
    }
    return (0);
}

// Main function: Process all heredocs in command list
int process_all_heredocs(t_minishell *shell)
{
    t_command *cmd;
    char *content;
    int should_expand;

    cmd = shell->cmd;
    while (cmd)
    {
        // debug_check_cmd_heredoc(cmd);

        // Process multiple heredocs in input_files (these get discarded)
        if (cmd->input_files)
        {
            int i = 0;
            while (cmd->input_files[i])
            {
                // printf("Reading heredoc (will discard) with delimiter: %s\n", cmd->input_files[i]);

                should_expand = should_expand_heredoc(shell, cmd->input_files[i]);
                content = read_heredoc_content(shell, cmd->input_files[i], should_expand);

                if (!content) // Ctrl+C was pressed
                {
                    shell->exit_code = 1;
                    return (0);
                }

                // printf("Content read (discarding): '%s'\n", content);
                free(content); // Discard this content
                i++;
            }
        }

        // Process the final heredoc (this one gets used as input)
        if (cmd->input_type == INPUT_HEREDOC && cmd->input_file)
        {
            // printf("Reading final heredoc with delimiter: %s\n", cmd->input_file);

            should_expand = should_expand_heredoc(shell, cmd->input_file);
            content = read_heredoc_content(shell, cmd->input_file, should_expand);

            if (!content) // Ctrl+C was pressed
            {
                shell->exit_code = 1;
                return (0);
            }

            // printf("Final content (will be used): '%s'\n", content);

            // Store content (replace delimiter with content)
            free(cmd->input_file);
            cmd->input_file = content;
        }

        cmd = cmd->next;
    }
    return (1); // Success
}