/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:10:17 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/25 15:32:09 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

char	has_space(char c)
{
	if ((c > 7 && c <= 13) || c == 32)
		return (1);
	return (0);
}

t_status	ms_isalpha(char c)
{
	if ((c > 64 && c < 91)
		|| (c > 96 && c < 123))
		return (On);
	return (Off);
}

t_status	ms_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (On);
	return (Off);
}

t_status	ms_strcmp(char *one, char *two)
{
	while (*one && *two && *one == *two)
	{
		one++;
		two++;
	}
	if (!*one && !*two)
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

char	*ms_strchr(char *str, int c)
{
	int		count;
	char	*str2;

	count = 0;
	str2 = (char *)str;
	while (str2[count] != '\0')
	{
		if (str2[count] == (char)c)
		{
			return (&str2[count]);
		}
		count++;
	}
	if (str2[count] == c)
		return (&str2[count]);
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

int	ms_strncmp(char *str1, char *str2, int n)
{
	unsigned char	*str3;
	unsigned char	*str4;
	int				count;

	str3 = (unsigned char *)str1;
	str4 = (unsigned char *)str2;
	count = 0;
	while ((count < n) && (str3[count] != '\0' || str4[count] != '\0'))
	{
		if (count < n && str3[count] != str4[count])
		{
			return (str3[count] - str4[count]);
		}
		count++;
	}
	return (0);
}
