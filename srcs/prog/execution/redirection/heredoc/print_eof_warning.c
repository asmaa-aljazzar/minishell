#include "minishell.h"

void print_eof_warning(char *delimiter)
{
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimiter, 2);
    ft_putendl_fd("')", 2);
}
