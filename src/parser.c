/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:11:57 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/20 16:46:29 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell>
#include <common.h>
#include <variable.h>

static char	*arr_bultings(void)
{
	char	*arr;

	arr = (char *)malloc(8 * sizeof(char));
	arr[0] = ms_strdup("echo");
	arr[1] = ms_strdup("cd");
	arr[2] = ms_strdup("pwd");
	arr[3] = ms_strdup("export");
	arr[4] = ms_strdup("unset");
	arr[5] = ms_strdup("env");
	arr[6] = ms_strdup("exit");
	arr[7] = '\0';
	return (arr);
}

static void	call_bulting(char *bulting, t_variable **var, char *line)
{
	if (ms_strcmp("echo", bulting))
		echo();
	if (ms_strcmp("cd", bulting))
		cd();
	if (ms_strcmp("pwd", bulting))
		pwd();
	if (ms_strcmp("export", bulting))
		export();
	if (ms_strcmp("unset", bulting))
		unset(var, line);
	if (ms_strcmp("env", bulting))
		env();
	if (ms_strcmp("exit", bulting))
		exit();
}

static t_status	check_bultins(char *line, t_variable **var)
{
	int		index;
	int		count;
	char	*arr_bultin;

	index = 0;
	arr_bultin = arr_bultings();
	while (line++ == ' ')
		count++;
	while (arr_bultin[index] && !ms_strcmp((line + count), arr_bultin[index]))
		index++;
	if (ms_strcmp((line + count), arr_bultin[index]))
	{
		call_bulting(arr_bultin[index], var,
			line + ms_strlen(arr_bultin[index] + 1));
		return (On);
	}
	return (Off);
}

void	parser(char *line, t_variable **var)
{
	if (!check_bultins(line, var))
		printf("command not found");
}
