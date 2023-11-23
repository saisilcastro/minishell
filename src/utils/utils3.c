/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:03:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/23 12:44:40 by lde-cast         ###   ########.fr       */
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

char	*ms_itoa(int n)
{
	char	buffer[12];
	int		index;
	char	sinal;

	if (n == 0)
		return (ms_strdup("0"));
	sinal = 0;
	index = 12;
	buffer[--index] = '\0';
	if (n < 0)
	{
		buffer[--index] = (n % 10) * -1 + '0';
		n /= 10;
		n = n * -1;
		sinal = '-';
	}
	while (n != 0)
	{
		buffer[--index] = (n % 10) + '0';
		n /= 10;
	}
	if (sinal == '-')
		buffer[--index] = sinal;
	return (ms_strdup(&buffer[index]));
}

t_status	has_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (On);
	return (Off);
}
