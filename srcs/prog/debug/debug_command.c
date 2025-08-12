#include "minishell.h"

void debug_command(const t_command *cmd)
{
    if (!cmd)
    {
        printf("[DEBUG] Command pointer is NULL.\n");
        return;
    }

    printf("---- Debugging Command at %p ----\n", (void *)cmd);

    // argv and argv_expanded
    if (cmd->argv)
    {
        printf("argv:\n");
        for (int i = 0; cmd->argv[i] != NULL; i++)
        {
            int expanded_flag = (cmd->argv_expanded) ? cmd->argv_expanded[i] : -1;
            printf("  argv[%d]: '%s'  | expanded: %d\n", i, cmd->argv[i], expanded_flag);
        }
    }
    else
    {
        printf("argv is NULL\n");
    }

    // Input redirection
    printf("Input type: %d\n", cmd->input_type);
    printf("Input file (last): %s\n", cmd->input_file ? cmd->input_file : "(null)");

    if (cmd->input_files)
    {
        printf("Input files (before last):\n");
        for (int i = 0; cmd->input_files[i] != NULL; i++)
            printf("  input_files[%d]: %s\n", i, cmd->input_files[i]);
    }
    else
    {
        printf("input_files is NULL\n");
    }

    // Output redirection
    printf("Output type: %d\n", cmd->output_type);
    printf("Output file (last): %s\n", cmd->output_file ? cmd->output_file : "(null)");

    if (cmd->output_files)
    {
        printf("Output files (before last):\n");
        for (int i = 0; cmd->output_files[i] != NULL; i++)
            printf("  output_files[%d]: %s\n", i, cmd->output_files[i]);
    }
    else
    {
        printf("output_files is NULL\n");
    }

    printf("heredoc_fd: %d\n", cmd->heredoc_fd);
    printf("Next command pointer: %p\n", (void *)cmd->next);

    printf("-----------------------------------\n");
}

