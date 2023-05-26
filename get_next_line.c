/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:31:02 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/26 17:11:08 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*free_archive frees the memory allocated to archive, sets it to NULL and
returns NULL*/
static char	*free_archive(char **archive)
{
	if (*archive)
	{
		free(*archive);
		*archive = NULL;
	}
	return (NULL);
}

static void	join_archive_and_buffer(char **archive, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*archive, buffer);
	free_archive(archive);
	*archive = temp;
}

/*extract_line looks the first occurence of '\n' in archive and returns all the
characters before it, it then updates archive by deleting all the characters
before '\n', and '\n' itself.
If no '\n'' is found in archive, extrcat_line returns archive and frees it*/
static char	*extract_line(char **archive)
{
	size_t	length;
	char	*line;
	char	*temp;

	if (ft_strchr(*archive, '\n'))
		length = ft_strchr(*archive, '\n') - *archive + 1;
	else
		length = ft_strlen(*archive);
	line = malloc((length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *archive, length + 1);
	if (ft_strchr(*archive, '\n'))
	{
		temp = ft_strjoin(ft_strchr(*archive, '\n') + 1, "");
		free_archive(archive);
		*archive = temp;
	}
	else
		free_archive(archive);
	return (line);
}

/*get_next_line reads up to BUFFER_SIZE bytes of the file pointed by fd into 
buffer. buffer is stored into the static variable archive at each iteration,
and the line is extracted from archive by the extract_line function
get_next_line returns the current line at each linebreak it encounters*/
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*archive = NULL;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!archive)
			archive = ft_strjoin("", buffer);
		else
			join_archive_and_buffer(&archive, buffer);
		if (ft_strchr(archive, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (!archive || !*archive)
		return (free_archive(&archive));
	return (extract_line(&archive));
}
