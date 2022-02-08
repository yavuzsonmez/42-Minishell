/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:33 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/02 10:12:43 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Return the value of the "HOME" environment var in the env list */

static char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*	Built-in command, replace the "PWD" environment variable by
*	the one specified by the parameter passed to 'cd'
*	and change the current directory
*/

void	ft_cd(t_list *lst, int err, char *home, t_env *tmp)
{
	char	buf[PATH_MAX];

	if (lst->cmd[1] != NULL && lst->cmd[2] != NULL && exit_positive(1, PWD))
		return ;
	tmp = lst->env;
	if (tmp == NULL && exit_positive(1, PWD))
		return ;
	home = get_home(tmp);
	if (lst->cmd[1] == NULL || ft_strcmp(lst->cmd[1], "~") == 0)
		err = chdir(home);
	else
		err = chdir(lst->cmd[1]);
	if (err != 0 && exit_positive(127, FILE_MISSING_MSG))
		return ;
	while (tmp != NULL && ft_strcmp(tmp->var, "PWD"))
	{
		tmp = tmp->next;
		if (tmp == NULL && exit_positive(1, PWD))
			return ;
	}
	free(tmp->value);
	getcwd(buf, PATH_MAX);
	tmp->value = ft_strdup(buf);
	if ((tmp->value == NULL && exit_positive(2, MALLOC_FAIL)) || exit_zero())
		return ;
}
