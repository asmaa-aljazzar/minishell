
#include "minishell.h"
void input_redirection(t_command *cmd)
{
    if (cmd->input_type == INPUT_FILE)
    {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0)
            {
                perror(cmd->input_file);
                exit(ERR_COMMAND_NOT_FOUND);
            } 
            if((dup2(fd, STDIN_FILENO) < 0)) 
            {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
            }
            //redirects standard input (stdin) to come from the file.
            close(fd);
    }
}