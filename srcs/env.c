/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:38 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/02 16:49:09 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Print the environment */

void	ft_env(t_list	*lst)
{
	t_env	*tmp;

	tmp = lst->env;
	if (lst->cmd[1] != NULL && exit_positive(127, FILE_MISSING_MSG))
		return ;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
	exit_zero();
}
