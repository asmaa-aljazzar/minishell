/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:34:44 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:34:47 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_str_format(va_list args, int printed_chars)
{
	char	*x;

	x = va_arg(args, char *);
	ft_putstr_fd(x, 1);
	printed_chars += ft_strlen(x);
	return (printed_chars);
}
