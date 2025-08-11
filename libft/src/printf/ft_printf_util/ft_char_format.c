/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:34:16 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:34:19 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_char_format(va_list args, int printed_chars)
{
	char	x;

	x = (char)va_arg(args, int);
	ft_putchar_fd(x, 1);
	printed_chars++;
	return (printed_chars);
}
