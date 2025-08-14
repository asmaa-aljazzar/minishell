#include "minishell.h"

#include "minishell.h"

//*#### Redirect stdin from the last input file in input_files array
// int main_redir_input_from_files(t_command *cmd)
// {
//     int fd;
//     int i;

//     if (!cmd->redir)
//         return 0;
//     i = 0;
//     while (cmd->input_files[i])
//         i++;
//     fd = open(cmd->input_files[i], O_RDONLY);
//     if (fd < 0)
//     {
//         ft_putstr_fd("minishell: ", STDERR_FILENO);
//         perror(cmd->input_files[i]);
//         return -1;
//     }
//     if (dup2(fd, STDIN_FILENO) < 0)
//     {
//         perror("dup2");
//         close(fd);
//         return -1;
//     }
//     close(fd);
//     return 0;
// }

int input_redirection(t_command *cmd, t_redirection *redir)
{
    int fd;

    if (!cmd || !redir)
        return 0; // No input redirection needed
    fd = open(redir->file, O_RDONLY);
    if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(redir->file);
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

int main_redir_input(t_command *cmd, t_redirection *redir)
{
    if (!cmd)
        return 0;
    if (redir->type == T_HEREDOC)
        if (setup_heredoc_input(redir) < 0)
            return (-1);
    if (redir->type == T_INPUT)
        if (input_redirection(cmd, redir) < 0)
            return -1;
    return 0;
}

int main_redir_output_open_file(const char *filename, int output_type)
{
    int flags = O_WRONLY | O_CREAT;
    int fd;

    if (output_type == T_APPEND)
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

int main_redir_output(t_command *cmd, t_redirection *redir)
{
	int fd;

	if (!cmd || !redir)
		return 0;
	fd = main_redir_output_open_file(redir->file, redir->type);
	if (fd < 0)
	{
		perror(redir->file);
		return -1;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

int main_redirection(t_minishell *ms)
{
    t_command *cmd;
    t_redirection *redir;

    cmd = ms->cmd;
    redir = cmd->redir;
    while (redir)
    {
        // fprintf(stderr, "%d\n", redir->type);
        if (redir->type == T_HEREDOC || redir->type == T_INPUT)
        {
            if (main_redir_input(cmd, redir) < 0)
                return -1;
        }
        else if (redir->type == T_OUTPUT || redir->type == T_APPEND)
        {
            if (main_redir_output(cmd, redir) < 0)
                return -1;
        }
        redir = redir->next;
    }
    return 0;
}
