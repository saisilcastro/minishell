/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/23 14:46:25 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

void	echo_execute(char *text, t_status newline)
{
	if (!text)
		return ;
	printf("%s", text);
	if (newline)
		printf("\n");
}
