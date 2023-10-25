/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:17:48 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/25 15:37:49 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	copy_list(t_variable **var)
// {
// 	t_variable	*var;

// 	t_variable
// }

//char	*copy_arr(char **arr, char **var)
//{
//	int			index;
//	char		*alpha_order;

//	index = 0;
//	while (arr[index])
//		index++;
//	alpha_order = (char *)malloc((index + 1) * sizeof (char *));
//	index = -1;
//	while (arr[++index])
//		alpha_order[index] = *ms_strdup(arr[index]);
//	alpha_order[index] = *ms_strdup("\0");
//	return (alpha_order);
//}

//char	*get_value(char *str_value)
//{
//	int		index;
//	char	*value;

//	if (value[0] == '"' || value[0] == 39)
//	{
//		value = (char *)malloc((ms_strlen(str_value) - 1) * sizeof(char));
//		index = 1;
//		while (value[index + 1] != '\0')
//		{
//			value[index] = str_value[index];
//			index++;
//		}
//	}
//	else
//	{
//		index = -1;
//		value = (char *)malloc((ms_strlen(str_value) + 1) * sizeof(char));
//		while (str_value[++index])
//			value[index] = str_value[index];
//	}
//	value[index] = '\0';
//	return (value);
//}

//char	*get_name(char *string)
//{
//	int			index;
//	int			size;
//	char		*name;

//	index = -1;
//	size = 0;
//	while (string[++index] && string[index] != '=')
//		size++;
//	if (!string[index])
//		return (0);
//	name = (char *)malloc((size + 1) * sizeof(char));
//	index = -1;
//	while (string[++index] && string[index] != '=')
//		name[index] = string[index];
//	name[index] = '\0';
//	return (name);
//}
