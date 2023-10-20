/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:50:09 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 16:54:32 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include <common.h>
#include <variable.h>

typedef struct s_echo	t_echo;
struct s_echo
{
	char	*data;
	t_echo	*next;
};

extern void		echo_set(t_echo *set);
extern void		echo_parse(t_echo **set, t_variable *var, char *command);
extern t_echo	*echo_push(char *data);
extern void		echo_next_last(t_echo **list, t_echo *set);
extern void		echo_execute(t_echo *set, t_status newline);
extern void		echo_pop(t_echo *list);

#endif