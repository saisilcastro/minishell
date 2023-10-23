/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:10:17 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 12:29:11 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <stdlib.h>

char	has_space(char c)
{
	if ((c > 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ms_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str && str[count] != '\0')
		count++;
	return (count);
}

int	ms_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

t_status	ms_strcmp(char *one, char *two)
{
	if (!*one || !*two)
		return (Off);
	while (*one && *two && *one == *two)
	{
		one++;
		two++;
	}
	if (!*one || !*two)
		return (On);
	return (Off);
}

char	*ms_strdup(char *str)
{
	char	*buffer;
	int		len;

	len = 0;
	while (*(str + len))
		len++;
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	len = 0;
	while (*(str + len))
	{
		*(buffer + len) = *(str + len);
		len++;
	}
	*(buffer + len) = '\0';
	return (buffer);
}

unsigned int	ms_strlcat(char *dest, const char *src, int size)
{
	size_t		sizedest;
	size_t		sizesrc;
	size_t		count;

	if (size == 0 && dest == 0)
		return (0);
	sizedest = ms_strlen(dest);
	sizesrc = ms_strlen((char *)src);
	count = 0;
	if (size > sizedest)
	{
		while (src[count] != 0 && count + sizedest < size - 1)
		{
			dest[sizedest + count] = src[count];
			count++;
		}
		dest[sizedest + count] = '\0';
		return (sizesrc + sizedest);
	}
	return (sizesrc + size);
}