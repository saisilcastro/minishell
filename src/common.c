/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:10:17 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 12:31:51 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char	has_space(char c)
{
	if ((c > 7 && c <= 13) || c == 32)
		return (1);
	return (0);
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
