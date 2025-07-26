
#include "minishell.h"

void debug_Display_t_command(t_minishell *minishell)
{
	int cmd_num = 0;
	t_command *cmd = minishell->cmd;

	while (cmd)
	{
		printf("─── Command #%d ───\n", cmd_num);

		printf("ARGV: ");
		if (cmd->argv)
		{
			int i = 0;
			while (cmd->argv[i])
			{
				printf("[%s] ", cmd->argv[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(null)\n");

		printf("Input Type: %d\n", cmd->input_type);
		printf("Input File: %s\n", cmd->input_file ? cmd->input_file : "(null)");
		printf("Output Type: %d\n", cmd->output_type);
		printf("Output File: %s\n", cmd->output_file ? cmd->output_file : "(null)");
		// Print input files list
		printf("Input Files: ");
		if (cmd->input_files)
		{
			int i = 0;
			while (cmd->input_files[i])
			{
				printf("[%s] ", cmd->input_files[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(null)\n");

		// Print output files list
		printf("Output Files: ");
		if (cmd->output_files)
		{
			int i = 0;
			while (cmd->output_files[i])
			{
				printf("[%s] ", cmd->output_files[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(null)\n");
		;

		printf("Next Command: %s\n\n", cmd->next ? "exists" : "NULL");

		cmd = cmd->next;
		cmd_num++;
	}
}