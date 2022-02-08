/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:24:28 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:45:29 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Create a new node of t_env type */

t_env	*new_node(void)
{
	t_env	*lstnew;

	lstnew = (t_env *)malloc(sizeof(t_env));
	if (lstnew == NULL)
		return (NULL);
	lstnew->next = NULL;
	return (lstnew);
}

/*	Create a new node of t_list type */

t_list	*ft_lstnew(void)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof(t_list));
	if (lstnew == NULL)
		return (NULL);
	lstnew->next = NULL;
	return (lstnew);
}

/*	Add a node to a t_env list */

void	addto_lst(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*	Add a node to a t_list list */

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
