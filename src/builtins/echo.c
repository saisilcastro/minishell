/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/25 15:39:29 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo_execute(char *text, t_status newline)
{
	if (!text)
		return ;
	printf("%s", text);
	if (newline)
		printf("\n");
}
