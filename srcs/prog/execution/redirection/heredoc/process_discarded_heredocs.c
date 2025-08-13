#include "minishell.h"

//static 
// int process_single_heredoc(t_minishell *ms, char *input_file)
// {
//     int should_expand = should_expand_heredoc(ms, input_file);
//     char *content = read_heredoc_content(ms, input_file, should_expand);

//     if (!content)
//     {
//         if (g_signal_received == SIGINT)
//         {
//             g_signal_received = 0; // Reset signal
//             ms->exit_code = 130;   // 128 + SIGINT(2)
//         }
//         else
//         {
//             ms->exit_code = 1;
//         }
//         return 0;
//     }
//     free(content);
//     return 1;
// }

int process_discarded_heredocs(t_minishell *ms, t_command *cmd)
{
//     int i;

    (void)ms;
    (void)cmd;
//     if (!cmd || !cmd->input_files)
//         return 1;

//     for (i = 0; cmd->input_files[i]; i++)
//     {
//         if (!process_single_heredoc(ms, cmd->input_files[i]))
//             return 0;
//     }
    return 1;
}
