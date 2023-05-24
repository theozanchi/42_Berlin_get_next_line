/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:31:02 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/24 13:39:52 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*extract_line looks the first occurence of '\n' in archive and returns all the
characters before it, it then updates archive by deleting all the characters
before '\n', and '\n' itself.
If no '\n'' is found in archive, extrcat_line returns archive and frees it*/
char	*extract_line(char **archive)
{
	size_t	length;
	char	*line;
	char	*temp;

	if (ft_strchr(*archive, '\n') == NULL)
	{
		length = ft_strlen(*archive);
		line = malloc((length + 1) * sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, *archive, length);
		free(*archive);
	}
	else
	{
		length = ft_strchr(*archive, '\n') - *archive + 1;
		line = malloc((length + 1) * sizeof(char));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, *archive, length + 1);
		temp = ft_strjoin(ft_strchr(*archive, '\n') + 1, "");
		free(*archive);
		*archive = temp;
	}
	return (line);
}

/*get_next_line reads up to BUFFER_SIZE bytes of the file pointed by fd into 
buffer. buffer is stored into the static variable archive at each iteration,
and the line is extracted from archive by the extract_line function
get_next_line returns the current line at each linebreak it encounters*/
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
		{
			if (archive != NULL)
				free(archive);
			return (NULL);
		}
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
