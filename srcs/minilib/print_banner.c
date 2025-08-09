
#include "minishell.h"

static void	print_banner_part1(void)
{
	print_slowly("\n\033[1;35m");
	print_slowly("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗    ");
	print_slowly(" ██╗     \n");
	print_slowly("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║    ");
	print_slowly(" ██║     \n");
	print_slowly("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║    ");
	print_slowly(" ██║     \n");
}

static void	print_banner_part2(void)
{
	print_slowly("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║    ");
	print_slowly(" ██║     \n");
	print_slowly("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗");
	print_slowly("███████╗\n");
	print_slowly("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝");
	print_slowly("╚══════╝\n");
	print_slowly("\033[0m\n");
}

void	print_banner(void)
{
	print_banner_part1();
	print_banner_part2();
}
