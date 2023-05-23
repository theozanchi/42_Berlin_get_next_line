/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:31:02 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/23 12:12:06 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	archive[10 * BUFFER_SIZE];
	char		*temp;
	ssize_t		bytes_read;
	char		*line;

	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read == -1)
		return (NULL);
	buffer[bytes_read] = '\0';
	temp = ft_strjoin(archive, buffer);
	line = extract_line_and_archive(temp, archive);
	if (line == NULL)
		return (NULL);
	free(temp);
	return (line);
}
