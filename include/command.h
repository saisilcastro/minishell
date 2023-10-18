/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:47:56 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/02 17:16:33 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdlib.h>

typedef struct s_flag		t_flag;
struct s_flag{
	char	*name;
	t_flag	*prev;
	t_flag	*next;
};

extern t_flag	*flag_push(char *name);
extern void		flag_next_first(t_flag **head, t_flag *set);
extern void		flag_next_last(t_flag **head, t_flag *set);
extern void		flag_pop(t_flag *set);

typedef struct s_command	t_command;
struct s_command{
	char	*run;
	t_flag	*flag;
};

#endif