/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:09:21 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 12:34:56 by lde-cast         ###   ########.fr       */
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

#endif