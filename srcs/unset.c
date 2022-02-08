/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:51 by ysonmez           #+#    #+#             */
/*   Updated: 2022/01/19 16:14:01 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Remove the specified environment variable
*		(Remove and free the corresponding node in the list)
*/

void	ft_unset(t_list	*lst)
{
	t_env	*tmp;
	t_env	*to_free;

	tmp = lst->env;
	if (lst->cmd[1] == NULL)
		return ;
	while (tmp->next != NULL && ft_strcmp(tmp->next->var, lst->cmd[1]))
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	if (tmp->next != NULL && tmp->next->next != NULL)
	{
		to_free = tmp->next;
		tmp->next = tmp->next->next;
	}
	else
	{
		to_free = tmp->next;
		tmp->next = NULL;
	}
	if (to_free == NULL)
		return ;
	free(to_free->var);
	free(to_free->value);
	free(to_free);
}
