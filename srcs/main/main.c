#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	t_minishell ms; // t_minishell struct
	(void) ac;
	(void) av;
	init (&ms, environ);
	main_loop (&ms); // go to the main loop // todo
	rl_clear_history (); // clear history before exit the shell
	return (0);
}
