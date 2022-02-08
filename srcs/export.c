/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:43 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/03 14:43:51 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Free the struct struct replace by export in the environment
*		- env variable name
*		- env variable's value
*		- the parent struct (the node)
*/

static void	free_oldnode(t_env *to_free)
{
	free(to_free->var);
	free(to_free->value);
	free(to_free);
}

/*	Check if the provided env variable provided by user already exist
*		If	yes, replace the value
*			not, create it
*/

static int	does_var_exist(t_list *lst, t_env *tmp)
{
	t_env	*env;

	env = lst->env;
	while (env != NULL && ft_strcmp(env->var, tmp->var))
	{
		env = env->next;
	}
	if (env == NULL)
		return (1);
	return (0);
}

/*	Add a new environment variable to the environment linked list
*		This new var is represented by a node with variable name and value
*/

void	ft_export(t_list *lst, t_env *new, t_env *tmp, t_env *to_free)
{
	tmp = lst->env;
	if (lst->cmd[1] == NULL)
		return ;
	if (ft_strchr(lst->cmd[1], '=') == NULL)
		return ;
	else
	{
		new = new_node();
		if (new == NULL && exit_positive(2, MALLOC_FAIL))
			return ;
		get_var_value(lst->cmd[1], new);
		if (does_var_exist(lst, new))
			addto_lst(&lst->env, new);
		else
		{
			while (ft_strcmp(tmp->next->var, new->var))
				tmp = tmp->next;
			to_free = tmp->next;
			new->next = to_free->next;
			tmp->next = new;
			free_oldnode(to_free);
		}
	}
	exit_zero();
}
