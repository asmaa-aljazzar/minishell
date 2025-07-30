/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:41:35 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/29 14:59:11 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global for signal handling
extern int g_signal_received;

// ============= Helper Functions for Variable Expansion =============

// Extract variable name from string starting after $
char *extract_var_name(char *str, int *index)
{
    char var_name[256];
    int j = 0;
    
    while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
    {
        var_name[j++] = str[*index];
        (*index)++;
    }
    var_name[j] = '\0';
    return (ft_strdup(var_name));
}

// Append string to result and free old result
char *append_to_result(char *result, char *to_append)
{
    char *temp;
    
    temp = result;
    result = ft_strjoin(result, to_append);
    free(temp);
    return (result);
}

// Handle $? expansion
char *expand_exit_code(t_minishell *shell, char *result, int *i)
{
    char *itoa_result;
    
    itoa_result = ft_itoa(shell->exit_code);
    result = append_to_result(result, itoa_result);
    free(itoa_result);
    *i += 2;
    return (result);
}

// Handle $VAR expansion
char *expand_env_var(t_minishell *shell, char *content, char *result, int *i)
{
    char *var_name;
    char *var_value;
    
    (*i)++; // Skip $
    var_name = extract_var_name(content, i);
    var_value = get_env_value(shell->env, var_name);
    result = append_to_result(result, var_value ? var_value : "");
    free(var_name);
    return (result);
}

// Handle single character append
char *append_single_char(char *result, char c)
{
    char str[2];
    
    str[0] = c;
    str[1] = '\0';
    return (append_to_result(result, str));
}

// Main expand variables function
char *expand_heredoc_variables(t_minishell *shell, char *content)
{
    char *result;
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
                result = expand_exit_code(shell, result, &i);
            else if (ft_isalpha(content[i + 1]) || content[i + 1] == '_')
                result = expand_env_var(shell, content, result, &i);
            else
                result = append_single_char(result, content[i++]);
        }
        else
            result = append_single_char(result, content[i++]);
    }
    return (result);
}

// ============= Helper Functions for Reading Heredoc =============

// Handle EOF warning
void print_eof_warning(char *delimiter)
{
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimiter, 2);
    ft_putendl_fd("')", 2);
}

// Check if line is delimiter
int is_delimiter_line(char *line, char *delimiter)
{
    size_t del_len = ft_strlen(delimiter);
    
    if (ft_strncmp(line, delimiter, del_len) == 0 && 
        ft_strlen(line) == del_len)
        return (1);
    return (0);
}

// Append line to content with newline
char *append_line_to_content(char *content, char *line)
{
    char *temp;
    
    temp = content;
    content = ft_strjoin(content, line);
    free(temp);
    temp = content;
    content = ft_strjoin(content, "\n");
    free(temp);
    return (content);
}

// Process a single line during heredoc reading
char *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break)
{
    *should_break = 0;
    if (g_signal_received == SIG_INT)
    {
        if (line)
            free(line);
        free(content);
        return (NULL);
    }
    if (!line)
    {
        print_eof_warning(delimiter);
        *should_break = 1;
        return (content);
    }
    if (is_delimiter_line(line, delimiter))
    {
        free(line);
        *should_break = 1;
        return (content);
    }
    content = append_line_to_content(content, line);
    free(line);
    return (content);
}

// Read lines until delimiter
char *read_until_delimiter(char *delimiter)
{
    char *content;
    char *line;
    int should_break;
    
    content = ft_strdup("");
    g_signal_received = SIG_NONE;

    while (1)
    {
        line = readline("> ");
        content = process_heredoc_readline(content, line, delimiter, &should_break);
        
        if (!content || should_break)
            break;
    }
    return (content);
}

// Main read heredoc function
char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    char *content;
    char *expanded;

    content = read_until_delimiter(delimiter);
    if (!content)
        return (NULL);

    if (should_expand && content)
    {
        expanded = expand_heredoc_variables(shell, content);
        free(content);
        content = expanded;
    }

    return (content);
}

// ============= Pipe Creation =============

// Create pipe with heredoc content for command execution
int create_heredoc_pipe(char *content)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
        return (-1);

    if (content && ft_strlen(content) > 0)
    {
        if (write(pipefd[1], content, ft_strlen(content)) == -1)
        {
            close(pipefd[0]);
            close(pipefd[1]);
            return (-1);
        }
    }

    close(pipefd[1]);
    return (pipefd[0]);
}

// ============= Heredoc Processing Helpers =============

// Check if delimiter should expand variables (not single-quoted)
int should_expand_heredoc(t_minishell *shell, char *delimiter)
{
    int i;

    i = 0;
    while (shell->tok[i])
    {
        if (shell->tok[i]->word && 
            ft_strncmp(shell->tok[i]->word, delimiter, ft_strlen(delimiter)) == 0)
            return (shell->tok[i]->qtype != QUOTE_SINGLE);
        i++;
    }
    return (1);
}

// Setup heredoc input for command execution
int setup_heredoc_input(t_command *cmd)
{
    int heredoc_fd;

    if (cmd->input_type != INPUT_HEREDOC || !cmd->input_file)
        return (0);

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
