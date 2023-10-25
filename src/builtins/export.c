/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/25 15:17:42 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

static void	alphabetical_order(char **arr, int n, int i)
{
	char	temp[50];
	int		j;

	if (i >= n - 1)
		return ;
	j = i + 1;
	while (j < n)
	{
		if (arr[j][0] < arr[i][0])
		{
			strcpy(temp, arr[i]);
			strcpy(arr[i], arr[j]);
			strcpy(arr[j], temp);
		}
		j++;
	}
	alphabetical_order(arr, n, i + 1);
}

void	print_envirolment(t_variable *var)
{
	extern char	**__environ;
	char		*alpha_order;
	t_variable	*curr;
	int			count;

	curr = var;
	count = 0;
	//alpha_order = copy_arr(__environ);
	while (alpha_order[count])
		count++;
	alphabetical_order(&alpha_order, count, 0);
	while (alpha_order)
	{
		printf("declare -x %s=\"%s\"\n", get_name(alpha_order),
			get_value(alpha_order + (ms_strlen(get_name(alpha_order)) + 1)));
		alpha_order++;
	}
}

static int	variable_check(t_variable **var, char *string)
{
	t_variable	*curr;

	curr = *var;
	while (curr)
	{
		if (ms_strcmp(curr->name, string))
			return (1);
		curr = curr->next;
	}
	return (0);
}

static void	new_value(t_variable **var, char *name, char *new_value)
{
	t_variable	*curr;

	curr = *var;
	while (curr && !ms_strcmp(curr->name, name))
		curr = curr->next;
	free(curr->value);
	curr->value = new_value;
}

t_variable	*validate_values(char *name, char *value)
{
	char		*name;
	char		*value;

	if (!ms_isalpha(name[0]) && name[0] != 95)
	{
		printf(PURPLE ">minishell: " WHITE
			"export: '%s': not a valid identifier\n", name);
		return (0);
	}
	if (value == NULL)
		return (variable_push(name, ms_strdup("\0")));
	if ((!ms_isalpha(value[0]) && value[0] != 95) && !ms_isdigit(value[0]))
		return (0);
	return (variable_push(name, value));
}

void	export(t_minishell *shell)
{
	t_command	*curr;
	char		*name;
	char		*value;

	curr = shell->cmd;
	if (!curr->next)
		print_envirolment(shell->var);
	curr = curr->next;
	while (curr)
	{
		name = get_name(curr->name);
		if (!ms_strchr(curr->name, '=') && !variable_check(shell->var, name))
			variable_next_first(shell->var, validate_values(name, NULL));
		value = ms_strdup(curr->name + ms_strlen(name));
		else if (variable_check(shell->var, name))
			new_value(shell->var, name, value);
		else
			variable_next_first(shell->var, validate_values(name, value));
		curr = curr->next;
		free(name);
	}
}