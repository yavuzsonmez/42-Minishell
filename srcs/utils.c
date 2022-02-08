/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:45:52 by home              #+#    #+#             */
/*   Updated: 2022/02/08 13:02:17 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_opt(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, ">>") == 0)
		return (3);
	else if (ft_strcmp(str, "<") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (5);
	else
		return (0);
}

/*	Count the number of strings in an array of strings */

int	count_str(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (-1);
	while (arr[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	on_opt(char a, char b)
{
	if (a == ' ' && b == '\0')
		return (1);
	else if (a == ' ' && b == '<')
		return (1);
	else if (a == ' ' && b == '>')
		return (1);
	else if (a == ' ' && b == '|')
		return (1);
	else
		return (0);
}
