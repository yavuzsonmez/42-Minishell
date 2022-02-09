/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:10:11 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/09 10:57:38 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Check if the full path of the binary in the system is provided */

static void	is_full_path(t_list *node)
{
	char	**tmp;
	int		i;

	i = 0;
	if (ft_strchr(node->cmd[0], '/') != NULL)
	{
		node->bin_path = ft_strdup(node->cmd[0]);
		tmp = ft_split(node->cmd[0], '/');
		if ((node->bin_path == NULL || tmp == NULL)
			&& exit_positive(2, MALLOC_FAIL))
			return ;
		while (tmp[i] != NULL)
		{
			i++;
		}
		i--;
		if (i >= 0)
		{
			free(node->cmd[0]);
			node->cmd[0] = ft_strdup(tmp[i]);
			if (node->cmd[0] == NULL && exit_positive(2, MALLOC_FAIL))
				return ;
		}
		ft_memfreeall((void **)tmp);
	}
}

/*	If the cmd is not a programm installed in the system
*	Keep the command path provided by the user is accesible
*	Otherwise command not found
*/

static void	not_system_cmd(t_list *node, char **buff)
{
	free(*buff);
	if (access(node->bin_path, X_OK) == 0)
		return ;
	else
	{
		free(node->bin_path);
		node->bin_path = NULL;
		return ;
	}
}

/*	Return the exact path where the command's
*	binary is in the filesystem
*/

static void	get_bin_path(t_list *node, char *env, int i)
{
	char	*buff;
	char	**tmp;
	char	*path;

	path = NULL;
	buff = ft_strjoin("/", node->cmd[0]);
	tmp = ft_split(env, ':');
	while (tmp[i] != NULL)
	{
		path = ft_strjoin(tmp[i], buff);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
		if (tmp[i] == NULL && ft_memfreeall((void **)tmp))
		{
			not_system_cmd(node, &buff);
			return ;
		}
	}
	if (node->bin_path != NULL)
		free(node->bin_path);
	free(buff);
	ft_memfreeall((void **)tmp);
	node->bin_path = path;
}

/*	Main function to get the path of the asked command */

void	get_path(t_list *node)
{
	char	*env;

	env = ft_getenv("PATH", node->env);
	if (env == NULL && exit_positive(2, MALLOC_FAIL))
		return ;
	is_full_path(node);
	get_bin_path(node, env, 0);
}
