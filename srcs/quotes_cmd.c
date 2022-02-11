/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:10:37 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/11 16:06:25 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	restructure_args(t_list *node, unsigned char q)
{
	char	**new;

	if (node->cmd[1] == NULL)
		return ;
	if (ft_strcmp(node->cmd[0], "echo") == 0
		&& ft_strcmp(node->cmd[1], "-n") == 0 && node->cmd[2] != NULL)
	{
		new = (char **)malloc(sizeof(char *) * 4);
		new[0] = ft_strdup(node->cmd[0]);
		new[1] = ft_strdup(node->cmd[1]);
		new[2] = copy_trimmed_str(node, q);
		new[3] = NULL;
	}
	else
	{
		new = (char **)malloc(sizeof(char *) * 3);
		new[0] = ft_strdup(node->cmd[0]);
		new[1] = copy_trimmed_str(node, q);
		new[2] = NULL;
	}
	ft_memfreeall((void **)node->cmd);
	node->cmd = new;
}

static void	trim_quotes_args(t_list *node, unsigned char q, int k)
{
	int				i;

	i = 1;
	while (node->cmd[i] != NULL)
	{
		q = which_quote(node->cmd[i]);
		if (q != 0)
			break ;
		i++;
	}
	if (q == 0)
		return ;
	node->quote_cmd = q;
	i = 1;
	while (node->cmd[i] != NULL)
	{
		k += count_quotes(node->cmd[i], q);
		i++;
	}
	if (k == 0 || (k % 2 != 0))
		return ;
	restructure_args(node, q);
}

/*	Realloc the command's string
*	and trimm a specific instance of quotes
*/

static void	restructure_bin(t_list *node, unsigned char q, int k)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(node->cmd[0]) - k + 1));
	if (buf == NULL && exit_positive(2, MALLOC_FAIL))
		return ;
	while (node->cmd[0][i] != '\0')
	{
		if (node->cmd[0][i] != q)
		{
			buf[j] = node->cmd[0][i];
			j++;
		}
		i++;
	}
	buf[j] = '\0';
	free(node->cmd[0]);
	node->cmd[0] = buf;
}

/*	Restructuring process of the command if we have a cmd
*	and not a heredoc for ex
*/

static void	trim_quotes_bin(t_list *node, unsigned char q, int k)
{
	q = which_quote(node->cmd[0]);
	if (q == 0)
		return ;
	k = count_quotes(node->cmd[0], q);
	if (k == 0 || (k % 2 != 0))
		return ;
	restructure_bin(node, q, k);
}

void	trim_quotes_cmd(t_list *node)
{
	*node->read_index += ft_strlen(node->cmd[0]);
	if (*node->read_index <= (int)ft_strlen(node->readline)
		&& node->readline[*node->read_index] != '\0'
		&& node->readline[*node->read_index] == ' ')
		*node->read_index += 1;
	trim_quotes_bin(node, 0, 0);
	trim_quotes_args(node, 0, 0);
	while (*node->read_index <= (int)ft_strlen(node->readline)
		&& node->readline[*node->read_index] != '\0')
	{
		if (on_opt(node->readline[*node->read_index],
				node->readline[*node->read_index + 1]))
		{
			*node->read_index += 3;
			break ;
		}
		else if (on_opt(node->readline[*node->read_index - 1],
				node->readline[*node->read_index]))
		{
			*node->read_index += 2;
			break ;
		}
		*node->read_index += 1;
	}
}
