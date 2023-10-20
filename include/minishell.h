/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/20 16:53:12 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <variable.h>
# include <builtins/echo.h>
# include <command.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define PURPLE "\033[1;35m"

// typedef struct s_command	t_command;
// {
// 	t_command	*cmd;
// 	t_variable	*args;
// };

typedef struct s_minishell	t_minishell;
struct s_minishell{
	t_variable	*var;
	t_command	*cmd;
};

extern void			shell_set(t_minishell *set);
extern void			shell_command(t_minishell *set);
extern void			shell_parse(t_minishell *set, char *command);
extern void			shell_pop(t_minishell *set);

extern void			export(int argc, char **argv, t_variable **var);
extern t_variable	*variable_node(char *string);
char				*get_name(char *string);
char				*get_value(char *string);

void				unset(t_variable **var, char *name);

void				*pwd(void);

void				env(void);

void	parser(char *line, t_variable **var);
#endif