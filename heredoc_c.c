#include "minishell.h"

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
}#include "minishell.h"

char *append_single_char(char *result, char c)
{
    char str[2];
    char  *append;
    
    str[0] = c;
    str[1] = '\0';
    append = append_to_result (result, str);
    return (append);
}#include "minishell.h"

char *append_to_result(char *result, char *to_append)
{
    char *temp;
    
    temp = result;
    result = ft_strjoin(result, to_append);
    free(temp);
    return (result);
}#include "minishell.h"

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
#include "minishell.h"

char *expand_env_var(t_minishell *shell, char *content, char *result, int *i)
{
    char *var_name;
    char *var_value;
    
    (*i)++;
    var_name = extract_var_name(content, i);
    var_value = get_env_value(shell->env, var_name);
    if (var_value == NULL)
        result = append_to_result(result, "");
    else
        result = append_to_result(result, var_value);
    free(var_name);
    return (result);
}
#include "minishell.h"

char *expand_exit_code(t_minishell *shell, char *result, int *i)
{
    char *itoa_result;
    
    itoa_result = ft_itoa(shell->exit_code);
    result = append_to_result(result, itoa_result);
    free(itoa_result);
    *i += 2;
    return (result);
}
#include "minishell.h"

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
#include "minishell.h"

char *extract_var_name(char *str, int *index)
{
    char var_name[256];
    char *res;
    int j = 0;
    
    while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
    {
        var_name[j++] = str[*index];
        (*index)++;
    }
    var_name[j] = '\0';
    res = ft_strdup (var_name);
    return (res);
}#include "minishell.h"

int is_delimiter_line(char *line, char *delimiter)
{
    size_t del_len = ft_strlen(delimiter);
    
    if (ft_strncmp(line, delimiter, del_len) == 0 && 
        ft_strlen(line) == del_len)
        return (1);
    return (0);
}#include "minishell.h"

void print_eof_warning(char *delimiter)
{
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimiter, 2);
    ft_putendl_fd("')", 2);
}#include "minishell.h"

int process_all_heredocs(t_minishell *minishell)
{
    t_command *cmd;

    cmd = minishell->cmd;
    while (cmd)
    {
        if (!process_discarded_heredocs(minishell, cmd))
            return (0);
            
        if (!process_final_heredoc(minishell, cmd))
            return (0);

        cmd = cmd->next;
    }
    return (1);
}
#include "minishell.h"

int process_discarded_heredocs(t_minishell *minishell, t_command *cmd)
{
    char *content;
    int should_expand;
    int i;
    
    if (!cmd->input_files)
        return (1);
    i = 0;
    while (cmd->input_files[i])
    {
        should_expand = should_expand_heredoc(minishell, cmd->input_files[i]);
        content = read_heredoc_content(minishell, cmd->input_files[i], should_expand);
        if (!content)
        {
            if (g_signal_received == SIGINT)
            {
                g_signal_received = 0; // Reset signal
                minishell->exit_code = 130; // 128 + SIGINT(2)
            }
            else
                minishell->exit_code = 1;
            return (0);
        }
        free(content);
        i++;
    }
    return (1);
}#include "minishell.h"

int process_final_heredoc(t_minishell *shell, t_command *cmd)
{
    char *content;
    int should_expand;
    
    if (cmd->input_type != INPUT_HEREDOC || !cmd->input_file)
        return (1);
        
    should_expand = should_expand_heredoc(shell, cmd->input_file);
    content = read_heredoc_content(shell, cmd->input_file, should_expand);

    if (!content)
    {
        if (g_signal_received == SIGINT)
        {
            g_signal_received = 0; // Reset signal
            shell->exit_code = 130; // 128 + SIGINT(2)
        }
        else
            shell->exit_code = 1;
        return (0);
    }

    free(cmd->input_file);
    cmd->input_file = content;
    return (1);
}#include "minishell.h"

// char *process_heredoc_readline(char *content, char *line, char *delimiter, int *should_break)
// {
//     *should_break = 0;
//     if (g_signal_received == SIG_INT)
//     {
//         if (line)
//             free(line);
//         free(content);
//         return (NULL);
//     }
//     if (!line)
//     {
//         print_eof_warning(delimiter);
//         *should_break = 1;
//         return (content);
//     }
//     if (is_delimiter_line(line, delimiter))
//     {
//         free(line);
//         *should_break = 1;
//         return (content);
//     }
//     content = append_line_to_content(content, line);
//     free(line);
//     return (content);
// }
#include "minishell.h"

char *read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    char *content;
    char *expanded;

    content = read_until_delimiter(delimiter);
    if (!content)
    {
        if (g_signal_received == SIGINT)
        {
            g_signal_received = 0; // Reset signal flag
            shell->exit_code = 1;
        }
        return (NULL);
    }

    if (should_expand && content)
    {
        expanded = expand_heredoc_variables(shell, content);
        free(content);
        content = expanded;
    }

    return (content);
}#include "minishell.h"

char *read_until_delimiter(char *delimiter)
{
    int pipefd[2];
    pid_t pid;
    char *content;
    
    if (pipe(pipefd) == -1)
        return (NULL);
    
    pid = fork();
    if (pid == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return (NULL);
    }
    
    if (pid == 0) // Child process
    {
        close(pipefd[0]);
        signal(SIGINT, SIG_DFL); // Allow Ctrl+C to kill child
        
        content = ft_strdup("");
        while (1)
        {
            char *line = readline("> ");
            
            if (!line)
            {
                print_eof_warning(delimiter);
                break;
            }
            
            if (is_delimiter_line(line, delimiter))
            {
                free(line);
                break;
            }
            
            content = append_line_to_content(content, line);
            free(line);
        }
        
        // Write content to pipe
        if (content)
        {
            write(pipefd[1], content, ft_strlen(content));
            free(content);
        }
        close(pipefd[1]);
        exit(0);
    }
    else // Parent process
    {
        int status;
        char buffer[4096];
        ssize_t bytes_read;
        
        close(pipefd[1]);
        
        // Wait for child to finish
        waitpid(pid, &status, 0);
        
        // Check if child was interrupted by signal
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            close(pipefd[0]);
            g_signal_received = SIGINT;
            return (NULL);
        }
        
        // Read content from pipe
        content = ft_strdup("");
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            char *temp;
            buffer[bytes_read] = '\0';
            temp = content;
            content = ft_strjoin(content, buffer);
            free(temp);
        }
        
        close(pipefd[0]);
        return (content);
    }
}#include "minishell.h"
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
#include "minishell.h"

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
#include "minishell.h"

// check if the token is not a redirection and argv inside one command
// not between pipes

void allocate_argv(t_minishell *minishell, int *argc, t_command **cmd, int *i)
{
	t_token *token = minishell->tok[*i];

	if (token->type == INPUT_PIPE || token->type == OUTPUT_PIPE)
	{
		(*cmd)->argv = malloc(sizeof(char *) * (*argc + 1));
		if (!(*cmd)->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
		*argc = 0;
		*cmd = (*cmd)->next;
	}
	else if (token->type != INPUT_FILE && token->type != INPUT_HEREDOC
		&& token->type != OUTPUT_FILE && token->type != OUTPUT_APPEND)
	{
		(*argc)++;
	}
}

#include "minishell.h"

// Last if is for last command after last pipe

void argv_for_commands(t_minishell *minishell)
{
	t_command *cmd = minishell->cmd;
	int i = 0;
	int argc = 0;

	while (minishell->tok[i])
	{
		allocate_argv(minishell, &argc, &cmd, &i);
		i++;
	}
	if (cmd)
	{
		cmd->argv = malloc(sizeof(char *) * (argc + 1));
		if (!cmd->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
	}
}

#include "minishell.h"

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

	minishell.envp = ft_strdup_double(environ);
	minishell.env = init_env(&minishell, environ);
	//!
	char *shlvl_str = getenv("SHLVL");
	int shlvl = shlvl_str ? ft_atoi(shlvl_str) : 0;
	shlvl += 1;
	char *new_shlvl = ft_itoa(shlvl);
	update_env_var(&minishell, "SHLVL", new_shlvl); 
	free(new_shlvl);
	//!
	main_loop(&minishell);
	rl_clear_history();
	return (0);
}// main_fork.c - Updated
#include "minishell.h"

void main_fork(t_minishell *shell)
{
    int status;
    pid_t pid;
    t_command *cmd = shell->cmd;
    
    if (!cmd || !cmd->argv || !cmd->argv[0])
    {
        shell->exit_code = 0;
        return;
    }
    
    // Handle builtin commands in parent (except in pipeline)
    if (is_builtin(cmd) && !cmd->next)
    {
        // Save original stdin/stdout
        int saved_stdin = dup(STDIN_FILENO);
        int saved_stdout = dup(STDOUT_FILENO);
        
        // Check redirections first
        if (!handle_redirection(shell))
        {
            shell->exit_code = 1;
            return;
        }
        
        // Apply redirections for builtin
        if (cmd->input_type == INPUT_FILE)
            input_redirection(cmd);
        if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
            handle_output_redirection(cmd);
        
        // Execute builtin
        compare_commands(shell);
        
        // Restore stdin/stdout
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
        
        return;
    }
    
    // Fork for external commands
    pid = fork();
    
    if (pid == -1)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror("fork");
        shell->exit_code = EXIT_FAILURE;
        return;
    }
    
    if (pid == 0) // Child process
    {
        setup_signals_child ();
        // Setup redirections
        main_redirection(shell);
        
        // Execute command
        compare_commands(shell);
        
        // Should never reach here
        exit(EXIT_FAILURE);
    }
    else // Parent process
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            shell->exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
        {
            shell->exit_code = 128 + WTERMSIG(status);
            if (WTERMSIG(status) == SIGINT)
                ft_putstr_fd("\n", STDOUT_FILENO);
        }
    }
}#include "minishell.h"
// main_loop.c - Updated section
void main_loop(t_minishell *minishell)
{
    setup_signals_parent();
    print_banner();
    while (1)
    {
        setup_signals_parent();
        init_shell(minishell);
        if (!minishell->input || !minishell->tok)
            continue;
        // exit_builtin(minishell);
        init_commands(minishell);
        expand_tokens(minishell);
        merge_words(minishell);
        argv_for_commands(minishell);
        tokens_to_commands(minishell);
        // if (!validate_pipeline(minishell))  // Add validation
        // {
        //     check_to_free(minishell);
        //     continue;
        // }
        if (!process_all_heredocs(minishell))
        {
            check_to_free(minishell);
            continue;
        }
        execute_pipeline(minishell); // Replace main_fork with execute_pipeline
        check_to_free(minishell);
    }
}// main_redirection.c - Updated
#include "minishell.h"

void main_redirection(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    
    if (!cmd)
        return;
    
    // Handle heredoc input
    if (cmd->input_type == INPUT_HEREDOC)
    {
        if (!setup_heredoc_input(cmd))
            exit(EXIT_FAILURE);
    }
    // Handle file input
    else if (cmd->input_type == INPUT_FILE)
    {
        input_redirection(cmd);
    }
    
    // Handle output redirection
    if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
    {
        handle_output_redirection(cmd);
    }
}
#include "minishell.h"

// — are called ASCII art, and specifically this style is known as a "FIGlet font".
//They are:
//Text rendered in blocky ASCII graphics, using characters like █, ║, ═, etc.
//Generated by FIGlet (short for Frank, Ian, and Glenn’s Letters), a tool that turns normal text into large, styled banners.
//The style I used above is a "ANSI Shadow" or "Big" font, which makes blocky uppercase letters look bold and powerful.

// Delay between characters (500 microseconds = 0.5ms)
void print_slowly(const char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        write(1, &line[i], 1);
        usleep(500);
        i++;
    }
}
void print_banner(void)
{
    const char *banner[] = {
        "\n",
        "\033[1;35m",
        "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n",
        "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n",
        "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n",
        "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n",
        "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n",
        "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝\n",
        "\033[0m",
        "\n",
        NULL
    };
    int i = 0;
    while (banner[i])
    {
        print_slowly(banner[i]);
        usleep(80000); // 80ms between each line
        i++;
    }
}
