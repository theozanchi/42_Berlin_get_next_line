/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:30:59 by tzanchi           #+#    #+#             */
/*   Updated: 2023/05/24 11:09:01 by tzanchi          ###   ########.fr       */
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

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;

	ptr = (char *)str;
	while (*ptr && (unsigned char)*ptr != (unsigned char)c)
		ptr++;
	if ((unsigned char)*ptr == (unsigned char)c)
		return (ptr);
	else
		return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	length;

	length = 0;
	while (src[length])
		length++;
	if (size == 0)
		return (length);
	while (--size && *src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (length);
}
