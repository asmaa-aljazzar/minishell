
#include "../../includes/libft.h"

void	ft_lstdelone(t_list *list, void (*del)(void *))
{
	if (!list)
		return ;
	del(list->content);
	free(list);
}
