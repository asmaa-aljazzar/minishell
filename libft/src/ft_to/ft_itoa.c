/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:14:01 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:14:03 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ftlength(int n);
static char	*allocate(int len);

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ftlength(n);
	result = allocate(len);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	i = len - 1;
	while (n != 0)
	{
		result[i] = ((n % 10) + 48);
		n = n / 10;
		i--;
	}
	result[len] = 0;
	return (result);
}

static char	*allocate(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '0';
	return (tmp);
}

static int	ftlength(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
