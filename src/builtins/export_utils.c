/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:17:48 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/23 11:29:39 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

static int	quote(char *string)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (string[index++] != '\0')
	{
		if (string[index] == 39 && string[index + 1] != '\0')
			while (string[index] == 39)
				index++;
		else if (string[index] == 39 && string[index + 1] == '\0')
			break ;
		count++;
	}
	return (count);
}

static int	double_quote(char *string)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (string[index++] != '\0')
	{
		if (string[index] == '"' && string[index + 1] != '\0')
			while (string[index] == '"')
				index++;
		else if (string[index] == '"' && string[index + 1] == '\0')
			break ;
		count++;
	}
	return (count);
}

static int	count_size(char *string)
{
	int	count;
	int	index;

	count = 0;
	index = -1;
	if (string[0] == 39)
		return (quote(string));
	else if (string[0] == '"')
		return (double_quote(string));
	while (string[++index] != '\0')
		count++;
	return (count + 1);
}

char	*get_value(char *string)
{
	int		index;
	char	*value;

	index = -1;
	value = (char *)malloc(count_size(string) * sizeof(char));
	if (string[0] == '"' || string[0] == 39)
	{
		index = 1;
		while (string[index + 1] != '\0')
		{
			value[index] = string[index];
			index++;
		}
	}
	else
		while (string[++index])
			value[index] = string[index];
	value[index] = '\0';
	return (value);
}

char	*get_name(char *string)
{
	int			index;
	int			size;
	char		*name;

	index = -1;
	size = 0;
	while (string[++index] && string[index] != '=')
		size++;
	if (!string[index])
		return (0);
	name = (char *)malloc((size + 1) * sizeof(char));
	index = -1;
	while (string[++index] && string[index] != '=')
		name[index] = string[index];
	name[index] = '\0';
	return (name);
}
