/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:31:02 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/23 17:18:26 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **archive)
{
	size_t	length;
	char	*line;
	char	*line_ptr;
	char	*archive_ptr;
	char	*linebreak_position;

	linebreak_position = ft_strchr(*archive, '\n');
	if (linebreak_position == NULL)
		length = ft_strlen(*archive);
	else
		length = linebreak_position - *archive + 1;
	line = malloc((length + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	line_ptr = line;
	archive_ptr = *archive;
	while (*archive_ptr && *archive_ptr != '\n')
		*line_ptr++ = *archive_ptr++;
	if (*archive_ptr == '\n')
		*line_ptr++ = '\n';
	*line_ptr = '\0';
	if (linebreak_position == NULL)
		free(*archive);
	else
		*archive = ft_strjoin(linebreak_position + 1, "");
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
