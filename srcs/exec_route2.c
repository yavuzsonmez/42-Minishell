/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_route2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:40:28 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/27 10:52:42 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	stdin_pipe_out(t_fd *fd)
{
	dup2((fd->pipes)[1], 1);
}

static void	pipe_in_file_out(t_fd *fd, int mode, t_list *lst)
{
	if (mode == FILE_OUT)
		fd->outfile = open(lst->fileout_path, O_RDWR
				| O_CREAT | O_TRUNC, 0666);
	else if (mode == FILE_APPEND)
		fd->outfile = open(lst->fileout_path, O_RDWR
				| O_CREAT | O_APPEND, 0666);
	dup2(fd->temp_fd, 0);
	dup2(fd->outfile, 1);
	close(fd->outfile);
}

static void	pipe_in_stdout(t_fd *fd)
{
	dup2(fd->temp_fd, 0);
}

static void	pipe_in_pipe_out(t_fd *fd)
{
	dup2(fd->temp_fd, 0);
	dup2((fd->pipes)[1], 1);
}

void	check_if_pipe(t_list *lst, t_fd *fd)
{
	if (lst->suffix == FILE_OUT)
		pipe_in_file_out(fd, FILE_OUT, lst);
	else if (lst->suffix == STDOUT)
		pipe_in_stdout(fd);
	else if (lst->suffix == PIPE_OUT)
		pipe_in_pipe_out(fd);
	else if (lst->suffix == FILE_APPEND)
		pipe_in_file_out(fd, FILE_APPEND, lst);
}
