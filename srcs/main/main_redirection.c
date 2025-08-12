#include "minishell.h"

#include "minishell.h"

//*#### Redirect stdin from the last input file in input_files array
int main_redir_input_from_files(t_command *cmd)
{
    int fd;
    int i;

    if (!cmd->input_files)
        return 0;
    i = 0;
    while (cmd->input_files[i])
        i++;
    fd = open(cmd->input_files[i - 1], O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(cmd->input_files[i - 1]);
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

//*#### Handle heredoc input redirection
int main_redir_input_heredoc(t_command *cmd)
{
    if (!setup_heredoc_input(cmd))
        return -1;
    return 0;
}

//*#### Handle input file redirection for INPUT_FILE input_type
int main_redir_input_file(t_command *cmd)
{
    if (input_redirection(cmd) != 0)
        return -1;
    return 0;
}

//*#### Controls input redirection logic by calling appropriate handlers
int main_redir_input(t_command *cmd)
{
    if (!cmd)
        return 0;

    if (cmd->input_files)
        return main_redir_input_from_files(cmd);

    if (cmd->input_type == INPUT_HEREDOC)
        return main_redir_input_heredoc(cmd);

    if (cmd->input_type == INPUT_FILE)
        return main_redir_input_file(cmd);

    return 0;
}

#include "minishell.h"

//*#### Opens a single output file with correct flags (append/truncate)
// Returns open file descriptor or -1 on error
int main_redir_output_open_file(const char *filename, int output_type)
{
    int flags = O_WRONLY | O_CREAT;
    int fd;

    if (output_type == OUTPUT_APPEND)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;

    fd = open(filename, flags, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        perror(filename);
        return -1;
    }
    return fd;
}

//*#### Redirects stdout to the given file descriptor
// Returns 0 on success, -1 on failure
int main_redir_output_redirect_last(int fd)
{
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return -1;
    }
    return 0;
}

//*#### Handles output redirection logic by opening all files
// and redirecting stdout to the last one
int main_redir_output(t_command *cmd)
{
    int fd;
    int i;
    int last_index;

    if (!cmd || !cmd->output_files)
        return 0;
    i = 0;
    while (cmd->output_files[i])
        i++;
    last_index = i - 1;
    for (i = 0; cmd->output_files[i]; i++)
    {
        fd = main_redir_output_open_file(cmd->output_files[i], cmd->output_type);
        if (fd < 0)
            return -1;

        if (i == last_index)
        {
            if (main_redir_output_redirect_last(fd) < 0)
                return -1;
        }
        close(fd);
    }
    return 0;
}


//*#### Main function controlling redirection
// - Calls input and output redirection handlers
int main_redirection(t_minishell *ms)
{
    t_command *cmd = ms->cmd;

    if (!cmd)
        return 0;

    if (main_redir_input(cmd) < 0)
        return -1;

    if (main_redir_output(cmd) < 0)
        return -1;

    return 0;
}
