
#include "minishell.h"


t_command *create_command(t_minishell *minishell)
{
	t_command *new = malloc(sizeof(t_command));
	if (!new)
		ft_exit(minishell, "malloc failed", EXIT_FAILURE);

	new->argv = NULL;
	new->input_type = INPUT_NONE;
	new->output_type = OUTPUT_NONE;
	new->input_file = NULL;
	new->input_files = NULL;
	new->output_file = NULL;
	new->output_files = NULL;
	new->next = NULL;

	return new;
}
