/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:12:21 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/25 14:10:33 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lst_clear_words(t_words **lst)
{
	t_words	*tmp;
	t_words	*rm;

	tmp = *lst;
	while (tmp != NULL)
	{
		rm = tmp->next;
		free(tmp->word);
		free(tmp);
		tmp = rm;
	}
	*lst = NULL;
}

/*	Free the t_env *env used to store the shell's environment */

int	lst_clear_env(t_env **env)
{
	t_env	*tmp;
	t_env	*to_free;

	if (*env == NULL)
		return (1);
	to_free = *env;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		free(to_free->var);
		free(to_free->value);
		free(to_free);
		to_free = tmp;
	}
	*env = NULL;
	return (1);
}

/*	Free the t_list *lst used for the user input's data of each command */

int	lst_clear_data(t_list **lst, t_list *tmp, t_list *to_free)
{
	if (*lst == NULL)
		return (1);
	to_free = *lst;
	if (to_free->readline != NULL)
		free(to_free->readline);
	*to_free->read_index = 0;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		if (to_free->cmd != NULL)
			ft_memfreeall((void **)to_free->cmd);
		if (to_free->bin_path != NULL)
			free(to_free->bin_path);
		if (to_free->filein_path != NULL)
			free(to_free->filein_path);
		if (to_free->fileout_path != NULL)
			free(to_free->fileout_path);
		if (to_free->hd_delimiter != NULL)
			free(to_free->hd_delimiter);
		free(to_free);
		to_free = tmp;
	}
	*lst = NULL;
	return (1);
}
