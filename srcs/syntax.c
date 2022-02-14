/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:44:25 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/14 12:11:52 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Separation of each command is based on the suffix and prefix
*		prefix can be : stdin, file_in, pipe_in or heredoc
*		suffix can be : stdout, pipe_out, file_out, file_append
*	>> From where we get data to where we redirect it after execution
*/

void	get_fix(t_list *node, char **arr, int i)
{
	if (ft_strcmp(arr[0], "|") == 0)
		node->prefix = PIPE_IN;
	else if (ft_strcmp(arr[0], "<") == 0)
		node->prefix = FILE_IN;
	else if (ft_strcmp(arr[0], "<<") == 0)
		node->prefix = HEREDOC;
	else if (ft_strcmp(arr[0], ">") == 0)
		node->prefix = FILE_OUT;
	else if (ft_strcmp(arr[0], ">>") == 0)
		node->prefix = FILE_APPEND;
	else
		node->prefix = STDIN;
	if (ft_strcmp(arr[i], "|") == 0)
		node->suffix = PIPE_OUT;
	else if (ft_strcmp(arr[i], ">") == 0)
		node->suffix = FILE_OUT;
	else if (ft_strcmp(arr[i], ">>") == 0)
		node->suffix = FILE_APPEND;
	else
		node->suffix = STDOUT;
}

/*	In case we need to read/write in a file,
*	get the file path and store it for eecution
*/

void	get_file_path(t_list *node, char **arr, int i)
{
	if (node->prefix == FILE_IN)
	{
		if (arr[1] == NULL)
			return ;
		node->filein_path = ft_strdup(arr[1]);
		if (node->filein_path == NULL && exit_positive(2, MALLOC_FAIL))
			return ;
		trim_quotes_prefix(node, 0, 0);
	}
	if (arr[i + 1] != NULL
		&& (node->suffix == FILE_OUT || node->suffix == FILE_APPEND))
	{
		node->fileout_path = ft_strdup(arr[i + 1]);
		if (node->fileout_path == NULL && exit_positive(2, MALLOC_FAIL))
			return ;
		trim_quotes_suffix(node, 0, 0);
	}
}

/*	In case we need to read/write in a file,
*	check if the file is accessible (if it already exists)
*	to avoid overwriting
*/

void	is_file_accessible(t_list *node)
{
	if (node->filein_path != NULL)
	{
		if (access(node->filein_path, F_OK) == 0)
			node->filein_access = true;
		else
			node->filein_access = false;
	}
	else if (node->fileout_path != NULL)
	{
		if (access(node->fileout_path, F_OK) == 0)
			node->fileout_access = true;
		else
			node->fileout_access = false;
	}
}

/*	if HEREDOC, get the delimiter */

void	heredoc_delimiter(t_list *node, char **arr)
{
	if (arr != NULL)
	{
		if ((arr[1] != NULL && is_opt(arr[1]) == 0))
		{
			node->hd_delimiter = ft_strdup(arr[1]);
			if (node->hd_delimiter == NULL && exit_positive(2, MALLOC_FAIL))
				return ;
			trim_quotes_prefix(node, 0, 0);
		}
		else
			return ;
	}
}
