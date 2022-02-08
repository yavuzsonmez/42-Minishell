/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_fix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:36:13 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/08 10:24:19 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	restructure_prefix(t_list *node, unsigned char q, int k, int i)
{
	char	*buf;
	char	*ptr;
	int		j;

	j = 0;
	if (node->prefix == FILE_IN)
		ptr = node->filein_path;
	else
		ptr = node->hd_delimiter;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(ptr) - k + 1));
	while (ptr[i] != '\0')
	{
		if (ptr[i] != q)
		{
			buf[j] = ptr[i];
			j++;
		}
		i++;
	}
	buf[j] = '\0';
	free(ptr);
	if (node->prefix == FILE_IN)
		node->filein_path = buf;
	else
		node->hd_delimiter = buf;
}

void	trim_quotes_prefix(t_list *node, unsigned char q, int k)
{
	char			*ptr;

	if (node->prefix == FILE_IN)
		ptr = node->filein_path;
	else
		ptr = node->hd_delimiter;
	q = which_quote(ptr);
	if (q == 0)
		return ;
	node->quote_in = q;
	k = count_quotes(ptr, q);
	if (k == 0 || (k % 2 != 0))
		return ;
	restructure_prefix(node, q, k, 0);
	while (node->readline[*node->read_index] != '\0')
	{
		if (on_opt(node->readline[*node->read_index],
				node->readline[*node->read_index + 1]))
		{
			*node->read_index += 1;
			break ;
		}
		*node->read_index += 1;
	}
}

static void	restructure_suffix(t_list *node, unsigned char q, int k)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buf = (char *)malloc(sizeof(char)
			* (ft_strlen(node->fileout_path) - k + 1));
	if (buf == NULL && exit_positive(2, MALLOC_FAIL))
		return ;
	while (node->fileout_path[i] != '\0')
	{
		if (node->fileout_path[i] != q)
		{
			buf[j] = node->fileout_path[i];
			j++;
		}
		i++;
	}
	buf[j] = '\0';
	free(node->fileout_path);
	node->fileout_path = buf;
}

void	trim_quotes_suffix(t_list *node, unsigned char q, int k)
{
	q = which_quote(node->fileout_path);
	if (q == 0)
		return ;
	node->quote_out = q;
	k = count_quotes(node->fileout_path, q);
	if (k == 0 || (k % 2 != 0))
		return ;
	restructure_suffix(node, q, k);
	while (node->readline[*node->read_index] != '\0')
	{
		if (on_opt(node->readline[*node->read_index],
				node->readline[*node->read_index + 1]))
		{
			*node->read_index += 1;
			break ;
		}
		*node->read_index += 1;
	}
}
