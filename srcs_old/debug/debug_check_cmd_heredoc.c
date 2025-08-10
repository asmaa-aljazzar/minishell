
#include "minishell.h"

void debug_check_cmd_heredoc(t_command *cmd)
{
    printf("=== DEBUG: Checking command ===\n");
    printf("input_type: %d\n", cmd->input_type);
    if (cmd->input_file)
        printf("input_file: %s\n", cmd->input_file);
    else
        printf("input_file: (null)\n");

    if (cmd->input_files)
    {
        printf("input_files array:\n");
        int i = 0;
        while (cmd->input_files[i])
        {
            printf("  [%d]: %s\n", i, cmd->input_files[i]);
            i++;
        }
    }
    else
    {
        printf("input_files: (null)\n");
    }
    printf("==============================\n");
}