/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:03:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/12 18:32:41 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_atoi(char *str)
{
	int	number;
	int	mul;

	number = 0;
	mul = 1;
	while (*str && has_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			mul = -1;
		str++;
	}
	while (*str && ms_isdigit(*str))
	{
		number *= 10;
		number += (*str - 48);
		str++;
	}
	return (number * mul);
}

void	join_path(char *path, char *file, char *buffer)
{
	int	i;

	i = -1;
	while (*path)
		*(buffer + ++i) = *path++;
	*(buffer + ++i) = '/';
	while (*file)
		*(buffer + ++i) = *file++;
	*(buffer + ++i) = '\0';
}
