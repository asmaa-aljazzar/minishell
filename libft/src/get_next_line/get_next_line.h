/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:         aaljazza <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:35 by aaljazza           #+#    #+#            */
/*   Updated: 2025/02/01 13:17:56 by aaljazza          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_file(int fd, char *line);
char	*ft_line(char *line);
char	*shift_buffer(char *line);
size_t	ft_strlen_g(const char *str);
char	*ft_strjoin_g(char *s1, char *s2);
char	*ft_strchr_g(char *s, int c);

#endif
