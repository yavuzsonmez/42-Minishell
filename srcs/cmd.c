/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:37:39 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/11 16:10:10 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Retrieve the command in the user input and store it
*	in the below allocated memory block
*/

static void	fill_cmd(t_list *node, char **arr, int i)
{
	int	j;

	j = 0;
	if (node->prefix == HEREDOC || node->prefix == FILE_IN)
		i--;
	while (j < i)
	{
		if (node->prefix == STDIN)
			node->cmd[j] = ft_strdup(arr[j]);
		else if (node->prefix == HEREDOC || node->prefix == FILE_IN)
			node->cmd[j] = ft_strdup(arr[j + 2]);
		else if (arr[j + 1] != NULL && is_opt(arr[j + 1]) == 0)
			node->cmd[j] = ft_strdup(arr[j + 1]);
		else
			node->cmd[j] = NULL;
		j++;
	}
	node->cmd[j] = NULL;
}

/*	allocate memory to store the cmd
*	provided by the user
*/

static void	alloc_cmd(t_list *node, char **arr, int i)
{
	if (arr == NULL || (is_opt(arr[0]) && arr[1] == NULL))
		return ;
	if (i == 0)
	{
		node->cmd = (char **)malloc(sizeof(char *) * 2);
		node->cmd[0] = ft_strdup(arr[0]);
		node->cmd[1] = NULL;
		return ;
	}
	if (arr[i + 1] == NULL)
		i++;
	if (node->prefix == HEREDOC || node->prefix == FILE_IN)
	{
		i--;
		node->cmd = (char **)malloc(sizeof(char *) * i);
	}
	else
		node->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	fill_cmd(node, arr, i);
}

/*	Get the command from the user input
*	parse it and handle quotes in commands and args
*/

void	get_cmd(t_list *node, char **arr, int i)
{
	alloc_cmd(node, arr, i);
	if (node->cmd == NULL || node->cmd[0] == NULL)
		return ;
	trim_quotes_cmd(node);
}

/*	Check if the command is a shell builtin command or not
*		Builtin : (cd; echo; env; exit; export; pwd; unset)
*/

void	is_builtin(t_list *node)
{
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "echo") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "env") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "exit") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "export") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "pwd") == 0)
		node->builtin = true;
	else if (ft_strcmp(node->cmd[0], "unset") == 0)
		node->builtin = true;
	else
		node->builtin = false;
}
