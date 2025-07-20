/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:32:44 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/20 17:46:32 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
* Tests for any character for which isalpha() or isdigit() is true. 
*/
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
