/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:10:17 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/09 15:27:01 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	ms_strcmp(char *one, char *two)
{
	while (*one && *two && *one == *two)
	{
		one++;
		two++;
	}
	if (!*one && !*two)
		return (0);
	return (*one - *two);
}

char	*ms_strdup(char *str)
{
	char	*buffer;
	int		len;

	len = 0;
	if (!str)
		return (NULL);
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
