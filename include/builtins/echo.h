/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:50:09 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 14:52:47 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

typedef struct s_echo	t_echo;
struct s_echo
{
	char	*data;
	t_echo	*next;
};

extern void		echo_set(t_echo *set);
extern t_echo	*echo_push(char *data);
extern void		echo_next_last(t_echo **list, t_echo *set);

# endif