/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:18:36 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/14 12:00:41 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cmd_count(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_wait(int cmd_cnt)
{
	while (cmd_cnt-- > 0)
	{
		waitpid(-1, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status))
			blocking_sighandler();
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
	}
}

int	exit_zero(void)
{
	g_exit_status = 0;
	return (1);
}

static void	find_criteria(t_list *lst, int *i, int *flag)
{
	if ((lst->suffix < 6 || lst->suffix > 9) && lst->suffix != -1
		&& ft_putstr_fd(PARSE_ERR_MSG, 2) && (*flag)++ == 0)
		g_exit_status = 1;
	else if ((lst->prefix < 1 || lst->prefix > 4) && lst->prefix != -1
		&& ft_putstr_fd(PARSE_ERR_MSG, 2) && (*flag)++ == 0)
		g_exit_status = 1;
	else if (((*i == 0 && lst->prefix == 3) || (lst->next == NULL
				&& lst->suffix == 8)) && ft_putstr_fd(PARSE_ERR_MSG, 2)
		&& (*flag)++ == 0)
		g_exit_status = 1;
	else if ((lst->prefix == HEREDOC && lst->hd_delimiter == NULL)
		&& ft_putstr_fd(PARSE_ERR_MSG, 2) && (*flag)++ == 0)
		g_exit_status = 1;
	else if ((lst->prefix == FILE_IN && access(lst->filein_path, F_OK) == -1)
		&& ft_putstr_fd(FILE_MISSING_MSG, 2) && (*flag)++ == 0)
		g_exit_status = 1;
	else if ((lst->prefix == FILE_IN && lst->filein_path != NULL
			&& access(lst->filein_path, R_OK) == -1
			&& ft_putstr_fd(FILE_ACCESS_MSG, 2) && (*flag)++ == 0))
		g_exit_status = 1;
	else if ((lst->suffix == FILE_OUT || lst->suffix == FILE_APPEND)
		&& lst->fileout_access == 1 && access(lst->fileout_path, W_OK) == -1
		&& ft_putstr_fd(FILE_ACCESS_MSG, 2) && (*flag)++ == 0)
		g_exit_status = 1;
}

int	check_fails(t_list *lst)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (lst != NULL)
	{
		find_criteria(lst, &i, &flag);
		if (flag == 1)
			return (1);
		i++;
		lst = lst->next;
	}
	return (0);
}
