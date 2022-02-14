/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:45:00 by home              #+#    #+#             */
/*   Updated: 2022/02/14 15:56:25 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Copies character of dst at the given index to
*	character of str at the given index
*/

void	copy(char *str, char *dst)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(dst);
	while (i < len)
	{
		str[i++] = dst[j++];
	}
}

/*	When every task is carried out, closes all pipes so that
*	file descriptor leaks are prevented
*/

void	close_pipes(t_fd *fd)
{
	close(fd->infile);
	close(fd->outfile);
	close(fd->pipes[0]);
	close(fd->pipes[1]);
	close(fd->temp_fd);
}

int	exit_positive(int exit_status, char *exit_text)
{
	g_exit_status = exit_status;
	if (exit_text != NULL)
		ft_putendl_fd(exit_text, 2);
	return (1);
}

int	cst_free(char *str, t_dollar *lst, int mode)
{
	if (mode == 0)
	{
		if (str != NULL)
			free(str);
	}
	else if (mode == 1)
	{
		lst->tmp = lst->var;
		while (lst->tmp)
		{
			free(lst->tmp->string);
			lst->tmp = lst->tmp->next;
		}
		if (lst->var != NULL)
			free(lst->var);
	}
	return (1);
}

int	expansion(t_list *tmp)
{
	char	*tmp2;

	tmp2 = NULL;
	if (tmp->cmd && env_to_value(tmp->cmd, tmp) == 1
		&& ft_putstr_fd(MALLOC_FAIL, 2))
		return (1);
	if (tmp->filein_path && tmp->quote_in != '\'')
	{
		tmp2 = tmp->filein_path;
		tmp->filein_path = path_replace(tmp->filein_path, tmp);
		free(tmp2);
		if (tmp->filein_path == NULL)
			return (1);
	}
	if (tmp->fileout_path && tmp->quote_out != '\'')
	{
		tmp2 = tmp->fileout_path;
		tmp->fileout_path = path_replace(tmp->fileout_path, tmp);
		free(tmp2);
		if (tmp->fileout_path == NULL)
			return (1);
	}
	return (0);
}
