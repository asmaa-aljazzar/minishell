#include "minishell.h"

// Returns 0 on success, -1 on failure
// int handle_redirection(t_minishell *shell)
// {
//     t_command *cmd = shell->cmd;

//     while (cmd)
//     {
//         if (cmd->output_files)
//         {
//             int i = 0;
//             int last_index = 0;

//             // Count output files
//             while (cmd->output_files[last_index])
//                 last_index++;

//             if (last_index == 0)
//             {
//                 cmd = cmd->next;
//                 continue;
//             }
//             last_index--; // index of last file

//             for (i = 0; cmd->output_files[i]; i++)
//             {
//                 int flags = O_WRONLY | O_CREAT;

//                 // Determine if append or truncate
//                 if (cmd->output_type == OUTPUT_APPEND)
//                     flags |= O_APPEND;
//                 else
//                     flags |= O_TRUNC;

//                 int fd = open(cmd->output_files[i], flags, 0644);
//                 if (fd < 0)
//                 {
//                     ft_putstr_fd("minishell: ", STDERR_FILENO);
//                     perror(cmd->output_files[i]);
//                     return -1;
//                 }

//                 // For the last output file, redirect stdout
//                 if (i == last_index)
//                 {
//                     if (dup2(fd, STDOUT_FILENO) < 0)
//                     {
//                         perror("dup2");
//                         close(fd);
//                         return -1;
//                     }
//                 }
//                 close(fd);
//             }
//         }
//         // Could add input files handling here if needed

//         cmd = cmd->next;
//     }

//     return 0;
// }
