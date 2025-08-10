#include "minishell.h"
void debug_commands(t_minishell *minishell)
{
    printf("=== DEBUG COMMANDS ===\n");
    t_command *cmd = minishell->cmd;
    int cmd_num = 0;
    
    while (cmd)
    {
        printf("Command[%d]:\n", cmd_num);
        
        // Print argv
        if (cmd->argv)
        {
            printf("  argv: [");
            for (int i = 0; cmd->argv[i]; i++)
            {
                printf("'%s'", cmd->argv[i]);
                if (cmd->argv[i + 1])
                    printf(", ");
            }
            printf("]\n");
        }
        else
        {
            printf("  argv: NULL\n");
        }
        
        // Print input info
        printf("  input_type: %d\n", cmd->input_type);
        printf("  input_file: %s\n", cmd->input_file ? cmd->input_file : "NULL");
        
        // Print output info
        printf("  output_type: %d\n", cmd->output_type);
        printf("  output_file: %s\n", cmd->output_file ? cmd->output_file : "NULL");
        
        // Print file arrays
        if (cmd->input_files)
        {
            printf("  input_files: [");
            for (int i = 0; cmd->input_files[i]; i++)
            {
                printf("'%s'", cmd->input_files[i]);
                if (cmd->input_files[i + 1])
                    printf(", ");
            }
            printf("]\n");
        }
        else
        {
            printf("  input_files: NULL\n");
        }
        
        if (cmd->output_files)
        {
            printf("  output_files: [");
            for (int i = 0; cmd->output_files[i]; i++)
            {
                printf("'%s'", cmd->output_files[i]);
                if (cmd->output_files[i + 1])
                    printf(", ");
            }
            printf("]\n");
        }
        else
        {
            printf("  output_files: NULL\n");
        }
        
        cmd = cmd->next;
        cmd_num++;
    }
    printf("===================\n");
}