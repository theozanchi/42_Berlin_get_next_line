/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:31:02 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/24 12:31:32 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **archive)
{
	size_t	length;
	char	*line;
	char	*linebreak_position;
	char	*temp;

	linebreak_position = ft_strchr(*archive, '\n');
	if (linebreak_position == NULL)
	{
		length = ft_strlen(*archive);
		line = malloc((length + 1) * sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, *archive, length);
		free(*archive);
		*archive = NULL;
	}
	else
	{
		length = linebreak_position - *archive + 1;
		line = malloc((length + 1) * sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, *archive, length + 1);
		temp = ft_strjoin(linebreak_position + 1, "");
		free(*archive);
		*archive = temp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*archive = NULL;
	ssize_t		bytes_read;
	char		*line;

	if (archive == NULL || !*archive)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		archive = ft_strjoin("", buffer);
		if (archive == NULL)
			return (NULL);
	}
	line = extract_line(&archive);
	if (line == NULL && !*archive)
		return (NULL);
	return (line);
}
