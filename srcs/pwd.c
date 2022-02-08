/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:49 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/02 16:56:57 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_list	*lst)
{
	t_env	*tmp;

	tmp = lst->env;
	while (tmp != NULL && ft_strcmp(tmp->var, "PWD"))
	{
		tmp = tmp->next;
	}
	if (tmp != NULL)
		ft_putendl_fd(tmp->value, 1);
}
