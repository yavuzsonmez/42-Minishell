/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:41:59 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/15 10:52:36 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_declarations(t_list *lst, char ***arr, int *size, int *i)
{
	*size = ft_lstsize(lst->env);
	*i = 0;
	if (*size > 0)
		*arr = ft_calloc(*size + 1, sizeof(char *));
	if (*arr == NULL)
		exit(1);
	(*arr)[*size] = NULL;
}

static void	clean_up_if_fail(char **arr, t_fd *fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	if (arr != NULL)
		free(arr);
	close(fd->pipes[1]);
	exit(127);
}

static void	create_env_node(t_list *lst, char **arr, int i)
{
	char	*tmp;

	tmp = NULL;
	arr[i] = ft_calloc(ft_strlen(lst->env->value)
			+ ft_strlen(lst->env->var) + 2, sizeof(char));
	if (arr[i] == NULL)
		exit(1);
	ft_memcpy(arr[i], lst->env->var, ft_strlen(lst->env->var));
	tmp = ft_strjoin(arr[i], "=");
	free(arr[i]);
	if (tmp == NULL)
		exit(1);
	arr[i] = tmp;
	tmp = ft_strjoin(arr[i], lst->env->value);
	free(arr[i]);
	if (tmp == NULL)
		exit(1);
	arr[i] = tmp;
}

void	command(t_list *lst, t_fd *fd)
{
	char	**arr;
	int		size;
	int		i;

	if (lst->cmd[0] == NULL && lst->prefix == PIPE_IN
		&& lst->suffix == STDOUT)
		exit(0);
	if (lst->prefix != HEREDOC && lst->prefix != FILE_IN
		&& lst->builtin == 0 && lst->bin_path == NULL
		&& ft_putstr_fd(CMD_MISSING_MSG, 2))
	{
		close(fd->pipes[1]);
		exit(127);
	}
	init_declarations(lst, &arr, &size, &i);
	while (i < size)
	{
		create_env_node(lst, arr, i);
		i++;
		lst->env = lst->env->next;
	}
	execve(lst->bin_path, lst->cmd, arr);
	clean_up_if_fail(arr, fd, size);
}
