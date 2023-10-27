/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:17:48 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/26 16:15:24 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_list(t_variable **var)
{
	t_variable	*curr_var;
	int			index;
	char		**arr;

	curr_var = *var;
	index = 0;
	while (curr_var)
	{
		index++;
		curr_var = curr_var->next;
	}
	arr = (char **)malloc((index + 1) * sizeof(char *));
	index = 0;
	curr_var = *var;
	while (curr_var)
	{
		arr[index++] = ms_strdup(curr_var->name);
		curr_var = curr_var->next;
	}
	arr[index] = ms_strdup("\0");
	return (arr);
}

char	**copy_arr(char **arr, char **var)
{
	int			index;
	int			index2;
	char		**alpha_order;

	index = 0;
	while (arr[index])
		index++;
	alpha_order = (char **)malloc((index + 1) * sizeof (char *));
	index = -1;
	while (arr[++index])
		alpha_order[index] = ms_strdup(arr[index]);
	index2 = -1;
	while (var[++index2])
		alpha_order[index] = ms_strdup(var[index]);
	alpha_order[index] = ms_strdup("\0");
	return (alpha_order);
}

char	*get_value(char *str_value)
{
	int		index;
	char	*value;

	if (value[0] == '"' || value[0] == 39)
	{
		value = (char *)malloc((ms_strlen(str_value) - 1) * sizeof(char));
		index = 1;
		while (value[index + 1] != '\0')
		{
			value[index] = str_value[index];
			index++;
		}
	}
	else
	{
		index = -1;
		value = (char *)malloc((ms_strlen(str_value) + 1) * sizeof(char));
		while (str_value[++index])
			value[index] = str_value[index];
	}
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
