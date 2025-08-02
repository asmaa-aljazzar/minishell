
#include "../../includes/libft.h"

char **ft_strdup_double(char **src)
{
    int i = 0;
    char **copy;

    while (src[i])
        i++;
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (src[i])
    {
        copy[i] = ft_strdup(src[i]);
        i++;
    }
    copy[i] = NULL;
    return copy;
}