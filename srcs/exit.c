/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:30 by ysonmez           #+#    #+#             */
/*   Updated: 2022/01/21 15:13:08 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Check if the exit status string provided is in the 1 byte range */

unsigned char	ft_atoi_unsigned_char(char *str)
{
	size_t			i;
	unsigned char	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == 48)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + ((str[i] - 48) % 10);
		i++;
	}
	return (result);
}

/*	Check if the exit status provided is only with digit */

static size_t	only_digit(char *status)
{
	int	i;

	i = 0;
	if (status[0] == '+' || status[0] == '-')
		i++;
	while (status[i] != '\0')
	{
		if (ft_isdigit(status[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*	Built-in exit function to quit the parent process
*	with the correct exit status
*/

void	ft_exit(t_list	*lst)
{
	(void)lst;
	ft_putendl_fd("exit", 1);
	if (lst->cmd[1] == NULL)
		exit(0);
	else if (lst->cmd[1] != NULL )
	{
		if (only_digit(lst->cmd[1])
			&& ft_putendl_fd("numeric argument required", 1))
			exit(255);
		else
		{
			if (lst->cmd[2] != NULL && ft_putendl_fd("too many arguments", 1))
				exit(1);
			else
			{
				if (lst->cmd[1][0] == '+' || lst->cmd[1][0] == '-')
					exit(256 + ft_atoi(lst->cmd[1]));
				exit(ft_atoi_unsigned_char(lst->cmd[1]));
			}
		}
	}
	else
		exit(255);
}
