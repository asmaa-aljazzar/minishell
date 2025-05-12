/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:         aaljazza <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:35 by aaljazza           #+#    #+#            */
/*   Updated: 2025/02/01 13:17:56 by aaljazza          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char *line, char *buffer)
{
	if (line)
		free(line);
	if (buffer)
		free(buffer);
	return (NULL);
}

char	*read_file(int fd, char *line)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(line, NULL));
	bytes_read = 1;
	while (!ft_strchr_g(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer, line));
		buffer[bytes_read] = '\0';
		line = ft_strjoin_g(line, buffer);
		if (!line)
			return (ft_free(buffer, NULL));
	}
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (ft_free(line, NULL));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*shift_buffer(char *buffer)
{
	char	*new_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (ft_free(buffer, NULL));
	new_buf = malloc(sizeof(char) * (ft_strlen_g(buffer) - i + 1));
	if (!new_buf)
		return (ft_free(buffer, NULL));
	i++;
	while (buffer[i])
		new_buf[j++] = buffer[i++];
	new_buf[j] = '\0';
	free(buffer);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = 0;
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (ft_free(buffer, NULL));
	line = ft_line(buffer);
	buffer = shift_buffer(buffer);
	return (line);
}
