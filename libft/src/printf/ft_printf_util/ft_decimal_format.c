/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:34:24 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:34:26 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_decimal_format(va_list args, int printed_chars)
{
	int		x;
	char	*str;

	x = va_arg(args, int);
	ft_putnbr_fd(x, 1);
	str = ft_itoa(x);
	if (str)
	{
		printed_chars += ft_strlen(str);
		free(str);
	}
	return (printed_chars);
}
