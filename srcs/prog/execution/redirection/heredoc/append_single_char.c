#include "minishell.h"

char *append_single_char(char *result, char c)
{
    char str[2];
    char  *append;
    
    str[0] = c;
    str[1] = '\0';
    append = append_to_result (result, str);
    return (append);
}