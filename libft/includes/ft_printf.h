/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:00:54 by baah-moh          #+#    #+#             */
/*   Updated: 2025/08/10 16:01:04 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

// Functions Prototype
int	ft_printf(const char *format, ...);
int	process_format(const char *format, va_list args);
int	ft_char_format(va_list args, int printed_chars);
int	ft_str_format(va_list args, int printed_chars);
int	ft_ptr_format(va_list args, int printed_chars);
int	ft_decimal_format(va_list args, int printed_chars);
int	ft_unsigned_format(va_list args, int printed_chars);
int	ft_upper_hex_format(va_list args, int printed_chars);
int	ft_lower_hex_format(va_list args, int printed_chars);

#endif
