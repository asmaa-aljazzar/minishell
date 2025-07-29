#include "minishell.h"

static int validate_and_count_exit_args(t_minishell *minishell);
static void exit_case1(t_minishell *minishell);

void exit_builtin(t_minishell *minishell)
{
	int arg_count;
	int exit_code;
	arg_count = validate_and_count_exit_args(minishell);
	if (arg_count == -1)
		return ;
	if (arg_count == 0)
		exit_case1(minishell);
	else if (arg_count == 1)
	{
		if (ft_is_valid_number(minishell->tok[1]->word))
			exit_code = ft_atoi(minishell->tok[1]->word) % 256;
		else
			exit_code = 0;
		check_to_free(minishell);
		free_env(minishell->env);
		free_2d(minishell->envp);
		rl_clear_history();
		exit(exit_code);
	}
	else
		printf("minishell: exit: too many arguments\n");
}

//*#### exit_case1
//- Handles the case where no argument is passed to "exit".
//- Frees resources and exits with code 0.
static void exit_case1(t_minishell *minishell)
{
	check_to_free(minishell);
	free_env(minishell->env);
	free_2d(minishell->envp);
	rl_clear_history();
	exit(0);
}

//*#### validate_and_count_exit_args
//- Validates whether the first token is "exit".
//- If not, returns -1 to indicate invalid command context.
//- If valid, counts the number of arguments following "exit".
//- Prints "exit" to stdout to mimic Bash behavior.
//- Returns the number of arguments after the "exit" command.
static int validate_and_count_exit_args(t_minishell *minishell)
{
	int count;

	count = 0;
	if (!minishell->tok || !minishell->tok[0] || strcmp(minishell->tok[0]->word, "exit") != 0)
		return (-1);
	while (minishell->tok[count + 1])
		count++;
	printf("exit\n");
	return (count);
}
