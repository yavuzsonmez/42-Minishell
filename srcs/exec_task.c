/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_task.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:53 by home              #+#    #+#             */
/*   Updated: 2022/02/03 14:30:20 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	PROTOTYPE */

void	builtin(t_list *lst)
{
	if (is_same(lst->cmd[0], "echo") == 1)
	{
		ft_echo(lst, 0, 0);
		exit_zero();
	}
	else if (is_same(lst->cmd[0], "cd") == 1)
		ft_cd(lst, 0, NULL, NULL);
	else if (is_same(lst->cmd[0], "pwd") == 1)
	{
		ft_pwd(lst);
		exit_zero();
	}
	else if (is_same(lst->cmd[0], "export") == 1)
		ft_export(lst, NULL, NULL, NULL);
	else if (is_same(lst->cmd[0], "unset") == 1)
	{
		ft_unset(lst);
		exit_zero();
	}
	else if (is_same(lst->cmd[0], "env") == 1)
		ft_env(lst);
	else if (is_same(lst->cmd[0], "exit") == 1)
		ft_exit(lst);
}

/*	Read from source FD into dest FD */

static void	read_into(void)
{
	char	str[2];

	while (1)
	{
		str[1] = '\0';
		if (read(0, str, 1) <= 0)
			break ;
		write(1, str, 1);
	}
}

/* Decide which task to execute based on in- and out FD */

void	execute_task(t_list *lst, t_fd *fd)
{
	if (lst->prefix == FILE_IN)
		read_into();
	else if (lst->prefix == HEREDOC)
		heredoc(lst, fd);
	else if (lst->builtin == 1)
		builtin(lst);
	else
		command(lst, fd);
}
