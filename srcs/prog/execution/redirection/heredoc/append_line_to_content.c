#include "minishell.h"

char *append_line_to_content(char *content, char *line)
{
    char *temp;
    
    temp = content;
    content = ft_strjoin(content, line);
    free(temp);
    temp = content;
    content = ft_strjoin(content, "\n");
    free(temp);
    return (content);
}