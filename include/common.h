/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:09:21 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 16:23:32 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

typedef enum e_status	t_status;
enum e_status{
	Off,
	On
};

extern char		has_space(char c);
extern t_status	ms_strcmp(char *one, char *two);
int				ms_isalpha(int c);
int				ms_strlen(const char *str);

#endif