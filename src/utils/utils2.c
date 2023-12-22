/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:39:37 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/21 10:28:49 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	if (!str1 || !str2)
		return (1);
	str3 = (unsigned char *)str1;
	str4 = (unsigned char *)str2;
	count = 0;
	while ((count < n) && (str3[count] != '\0' && str4[count] != '\0'))
	{
		if (count < n && str3[count] != str4[count])
			return (str3[count] - str4[count]);
		count++;
	}
	if (str3[count] || str4[count])
		return (str3[count] - str4[count]);
	return (0);
}

int	ms_name_cmp(char *str1, char *str2, int n)
{
	int	count;

	count = 0;
	while ((count <= n))
	{
		if (str1[count] == '\0' || str2[count] == '\0')
			break ;
		if (count < n && str1[count] != str2[count])
			return (str1[count] - str2[count]);
		count++;
	}
	if (!str1[count] && !str2[count])
		return (0);
	if (str1[count] && str1[count] == ' ')
		return (0);
	if ((str1[count] && str1[count] == '\'') || str1[count] == '"'
		|| str1[count] == '$' || str1[count] == '=')
		return (0);
	return (1);
}

void	ms_putstr_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s == 0)
		return ;
	while (s[c] != '\0')
	{
		write(fd, &s[c], 1);
		c++;
	}
}
