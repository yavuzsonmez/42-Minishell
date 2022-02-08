/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:35 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/02 16:44:40 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Display message on screen, writes each given STRING to standard output
*	With a space between each and a newline after the last one.
*/

void	ft_echo(t_list	*lst, int i, int nl)
{
	if (lst->cmd[1] == NULL && ft_putstr_fd("\n", 1))
		return ;
	if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		i = 2;
		nl = 0;
	}
	else
	{
		i = 1;
		nl = 1;
	}
	while (lst->cmd[i] != NULL)
	{
		if (lst->cmd[i + 1] != NULL && ft_putstr_fd(lst->cmd[i], 1))
			ft_putstr_fd(" ", 1);
		else if (lst->cmd[i + 1] == NULL && nl == 0
			&& ft_putstr_fd(lst->cmd[i], 1))
			return ;
		else if (lst->cmd[i + 1] == NULL && nl == 1
			&& ft_putendl_fd(lst->cmd[i], 1))
			return ;
		i++;
	}
}
