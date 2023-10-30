/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:17:48 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/27 16:39:39 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <minishell.h>

char	**copy_list(t_variable *var)
{
	t_variable	*curr_var;
	char		*join;
	int			index;
	char		**arr;

	curr_var = var;
	index = 0;
	if (!var)
		return (0);
	while (curr_var)
	{
		index++;
		curr_var = curr_var->next;
	}
	arr = (char **)malloc((index + 1) * sizeof(char *));
	index = 0;
	curr_var = var;
	while (curr_var)
	{
		join = ms_strjoin(ms_strjoin(curr_var->name, "="), curr_var->value);
		arr[index++] = ms_strdup(join);
		curr_var = curr_var->next;
		free (join);
	}
	arr[index] = ms_strdup("\0");
	return (arr);
}

char	**copy_arr(char **var)
{
	int			index;
	int			index2;
	int			index3;
	char		**alpha_order;
	extern char	**__environ;

	index = 0;
	index3 = -1;
	while (__environ && __environ[index])
		index++;
	while (var[++index3] && *var[index3])
		index++;
	alpha_order = (char **)malloc((index + 1) * sizeof (char *));
	index = -1;
	while (__environ[++index])
		alpha_order[index] = ms_strdup(__environ[index]);
	index2 = -1;
	while (var[++index2] && *var[index2])
	{
		alpha_order[index] = ms_strdup(var[index2]);
		index++;
	}
	alpha_order[index] = ms_strdup("\0");
	return (alpha_order);
}

char	*get_value(char *str_value)
{
	int		index;
	char	*value;

	if (!str_value)
		return (ms_strdup("\0"));
	value = (char *)malloc((ms_strlen(str_value) - 1) * sizeof(char));
	index = -1;
	value = (char *)malloc((ms_strlen(str_value) + 1) * sizeof(char));
	while (str_value[++index])
		value[index] = str_value[index];
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
