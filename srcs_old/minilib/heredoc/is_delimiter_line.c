#include "minishell.h"

int is_delimiter_line(char *line, char *delimiter)
{
    size_t del_len = ft_strlen(delimiter);
    
    if (ft_strncmp(line, delimiter, del_len) == 0 && 
        ft_strlen(line) == del_len)
        return (1);
    return (0);
}