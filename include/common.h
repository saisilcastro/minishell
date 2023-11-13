/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:09:21 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/13 15:56:13 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <minishell.h>

typedef enum e_status	t_status;
enum e_status{
	Off,
	On
};

extern char		has_space(char c);
extern int		ms_atoi(char *str);
extern int		ms_strcmp(char *one, char *two);
extern t_status	ms_isalpha(char c);
extern char		*ms_strdup(char *str);
extern char		*ms_strchr(char *str, int c);
extern t_status	ms_isdigit(char c);
extern int		ms_strlen(const char *str);
extern int		ms_strncmp(char *str1, char *str2, int n);
extern int		ms_name_cmp(char *str1, char *str2, int n);
extern void		ms_putstr_fd(char *s, int fd);
extern void		join_path(char *path, char *file, char *buffer);
extern char		*ms_itoa(int n);

#endif