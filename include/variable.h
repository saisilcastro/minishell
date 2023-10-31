/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:59:55 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/31 12:17:27 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_H
# define VARIABLE_H

# include <minishell.h>

typedef struct s_variable	t_variable;
struct s_variable
{
	char		*name;
	char		*value;
	t_variable	*next;
};

extern void			variable_set(t_variable *set);
extern t_variable	*variable_push(char *name, char *value);
extern void			variable_next_first(t_variable **list, t_variable *set);
extern void			variable_next_last(t_variable **list, t_variable *set);
extern t_variable	*variable_search(t_variable *list, char *name);
extern void			variable_delete(t_variable **list, char *name);
extern void			variable_pop(t_variable *list);
extern				int	value_position(char *list);

#endif