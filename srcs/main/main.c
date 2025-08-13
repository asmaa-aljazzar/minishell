#include "minishell.h"

int main(int ac, char **av, char **environ)
{
	t_minishell ms;
	(void) ac;
	(void) av;
	setup_signals_parent();
	init (&ms, environ, av[0]);
	main_loop (&ms); // go to the main loop // todo
	rl_clear_history (); // clear history before exit the shell
	return (0);
}
