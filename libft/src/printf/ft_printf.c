/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:35:08 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:35:10 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			printed_chars;

	printed_chars = 0;
	va_start (args, format);
	printed_chars = process_format (format, args);
	va_end (args);
	return (printed_chars);
}
