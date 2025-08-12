#include "minishell.h"

char *expand_exit_code(t_minishell *shell, char *result, int *i)
{
    char *itoa_result;
    
    itoa_result = ft_itoa(shell->exit_code);
    result = append_to_result(result, itoa_result);
    free(itoa_result);
    *i += 2;
    return (result);
}