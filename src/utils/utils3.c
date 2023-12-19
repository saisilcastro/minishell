/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:03:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/18 19:42:42 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

long long	ms_atol(char *nptr)
{
	long				i;
	long				sign;
	unsigned long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (has_space(nptr[i]))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ms_isdigit(nptr[i]))
	{
		res *= 10;
		res = res + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
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

t_status	has_redirect(t_command *cmd)
{
	if (!cmd)
		return (Off);
	if (!cmd->flag_quotes && (!ms_strncmp(cmd->name, "<", 1)
			|| !ms_strncmp(cmd->name, ">", 1)
			|| !ms_strncmp(cmd->name, "<<", 2)
			|| !ms_strncmp(cmd->name, ">>", 2)))
		return (On);
	return (Off);
}
