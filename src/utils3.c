/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:03:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/08 14:56:03 by lde-cast         ###   ########.fr       */
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
