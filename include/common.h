/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:09:21 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/18 19:43:15 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <minishell.h>

typedef enum e_status	t_status;
enum e_status
{
	Off,
	On
};

extern char			has_space(char c);
extern long long	ms_atol(char *str);
extern int			ms_strcmp(char *one, char *two);
extern t_status		ms_isalpha(char c);
extern char			*ms_strdup(char *str);
extern char			*ms_strchr(char *str, int c);
extern t_status		ms_isdigit(char c);
extern int			ms_strlen(const char *str);
extern int			ms_strncmp(char *str1, char *str2, int n);
extern int			ms_name_cmp(char *str1, char *str2, int n);
extern void			ms_putstr_fd(char *s, int fd);
extern char			*ms_itoa(int n);
extern t_status		has_special(char c);

#endif