
#include "minishell.h"

//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Enter an infinite loop to display prompts.
//* 3. Clear the history if the loop has been broken.
int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_minishell minishell;
	init(&minishell);

	minishell.envp = ft_strdup_double(environ);
	minishell.env = init_env(&minishell, environ);
	//!
	char *shlvl_str = getenv("SHLVL");
	int shlvl = shlvl_str ? ft_atoi(shlvl_str) : 0;
	shlvl += 1;
	char *new_shlvl = ft_itoa(shlvl);
	update_env_var(&minishell, "SHLVL", new_shlvl); 
	free(new_shlvl);
	//!
	main_loop(&minishell);
	rl_clear_history();
	return (0);
}