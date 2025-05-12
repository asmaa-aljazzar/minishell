/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:32:30 by aaljazza          #+#    #+#             */
/*   Updated: 2025/02/15 11:32:32 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif
# include <stdlib.h>

char	*get_next_line(int fd);

char	*ft_gnl_strdup(char *s);
char	*ft_gnl_substr(char *s, unsigned int start, size_t len);
char	*ft_gnl_strjoin(char *s1, char *s2);
void	fill_str(char *res, char *s1, char *s2);

#endif
