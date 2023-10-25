/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/25 15:15:30 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <variable.h>
# include <builtins/echo.h>
# include <command.h>
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define PURPLE "\033[1;35m"

typedef struct s_minishell	t_minishell;
struct s_minishell{
	t_variable	*var;
	t_command	*cmd;
	void		(*builtin)(t_minishell *set, char *command);
};

extern void	shell_set(t_minishell *set);
extern void	shell_command(t_minishell *set);
extern void	shell_parse(t_minishell *set, char *command);
extern void	shell_loop(t_minishell *set);
extern void	shell_pop(t_minishell *set);

extern void	export(t_minishell *shell);
extern void	expansion(t_command **list, t_variable *var);
extern char	*get_name(char *string);
extern char	*get_value(char *str_value);
extern char	*copy_arr(char **arr, t_variable *var);

#endif