/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:30:59 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/22 18:16:02 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (*str++)
		length++;
	return (length);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	char	*output_ptr;

	output = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	output_ptr = output;
	while (*s1)
		*output_ptr++ = *s1++;
	while (*s2)
		*output_ptr++ = *s2++;
	*output_ptr = '\0';
	return (output);
}

size_t	get_line_length(char *str)
{
	size_t	length;

	length = 0;
	while (*str && *str != '\n')
	{
		str++;
		length++;
	}
	if (*str == '\n')
		length++;
	return (length);
}

char	*extract_line_and_archive(char *buffer, char *archive)
{
	size_t	length;
	char	*line;
	char	*ptr;

	length = get_line_length(buffer);
	line = malloc((length + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ptr = line;
	while (*buffer != '\n')
		*ptr++ = *buffer++;
	if (*buffer == '\n')
	{
		*ptr = '\n';
		buffer++;
	}
	*++ptr = '\0';
	while (*buffer)
	{
		*archive++ = *buffer++;
	}
	*archive = '\0';
	return (line);
}
