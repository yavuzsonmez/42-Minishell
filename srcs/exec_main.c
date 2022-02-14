/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:28 by home              #+#    #+#             */
/*   Updated: 2022/02/14 15:18:03 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	exec_main.c is the core of the "exec" filegroup */

/*	Objective of the "exec" filegroup is to prepare the input for
*	execution of the task,
*	to determine and then set the directions of in- and output,
*	lastly, to execute the task
*		Order of execution: exec_main.c -> exec_route.c -> exec_task.c
*/

static void	forkless_processing(t_list *lst, t_fd *fd)
{
	int	stdincpy;
	int	stdoutcpy;

	stdincpy = dup(0);
	stdoutcpy = dup(1);
	sourceof_in_out(lst, fd);
	execute_task(lst, fd);
	close(fd->temp_fd);
	fd->temp_fd = dup(fd->pipes[0]);
	close(fd->pipes[0]);
	close(fd->pipes[1]);
	dup2(stdincpy, 0);
	dup2(stdoutcpy, 1);
	close(stdincpy);
	close(stdoutcpy);
}

/* Child Process */

static void	child(t_list *lst, t_fd *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd->pipes[0]);
	sourceof_in_out(lst, fd);
	execute_task(lst, fd);
	close(fd->pipes[1]);
	exit(0);
}

/* Parent Process */

static void	parent(t_fd *fd, t_list *lst, pid_t pid)
{
	close(fd->pipes[1]);
	if (lst->prefix == HEREDOC)
		waitpid(pid, &g_exit_status, 0);
	close(fd->temp_fd);
	fd->temp_fd = dup(fd->pipes[0]);
	close(fd->pipes[0]);
}

/*	Main execution block of the exec filegroup */

static int	tasker(t_list *tmp, t_fd *fd, int cmd_cnt)
{
	pid_t	pid;

	while (tmp != NULL)
	{
		if (expansion(tmp) == 1 && ft_putstr_fd(MALLOC_FAIL, 2))
			return (0);
		if (pipe(fd->pipes) < 0)
			exit (1);
		if (tmp->builtin == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(1);
			else if (pid == 0)
				child(tmp, fd);
			else
				parent(fd, tmp, pid);
		}
		else if (tmp->builtin == 1)
			forkless_processing(tmp, fd);
		tmp = tmp->next;
	}
	ft_wait(cmd_cnt);
	return (0);
}

void	pipex(t_list *lst)
{
	t_fd	fd;
	int		cmd_cnt;
	t_list	*tmp;

	tmp = lst;
	if (lst->prefix == -1 && lst->suffix == -1 && exit_zero())
		return ;
	fd.temp_fd = dup(0);
	cmd_cnt = cmd_count(tmp);
	if (check_fails(tmp) == 1)
	{
		close_pipes(&fd);
		return ;
	}
	tasker(tmp, &fd, cmd_cnt);
	close_pipes(&fd);
}
