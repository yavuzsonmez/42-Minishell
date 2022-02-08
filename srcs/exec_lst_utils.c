/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:16:29 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/20 18:10:39 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//test

t_words	*ft_wordsnew(void *content)
{
	t_words	*new_struct;

	new_struct = malloc(sizeof(t_words));
	if (new_struct == 0)
		return (0);
	new_struct->word = content;
	new_struct->next = NULL;
	return (new_struct);
}

/*	Executes the command */

int	ft_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
