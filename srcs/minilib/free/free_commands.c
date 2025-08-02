
#include "minishell.h"
void free_commands(t_minishell *minishell)
{
    t_command *current = minishell->cmd;
    t_command *next;
    
    while (current)
    {
        next = current->next;
        if (current->argv)
            free(current->argv);
        if (current->input_file)
            free(current->input_file);
        if (current->output_file)
            free(current->output_file);
        free_file_list(current->input_files);
        free_file_list(current->output_files);
        free(current);
        current = next;
    }
    minishell->cmd = NULL;
}