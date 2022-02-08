/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_hd_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:56:17 by ysonmez           #+#    #+#             */
/*   Updated: 2022/01/25 14:43:39 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	count the number of
		Heredoc, file_in, file_out, file_append
*	without space after the path or the delimiter
*	to allocate memory and fix parsed data for execution
*/

static int	count_file_hd(char **arr)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
			count++;
		else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
			count++;
		if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
			count++;
		else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
			count++;
		i++;
	}
	return (count);
}

/*	Create new string to get the operator
*	separated from delimiter or file path
*	from "<<EOF" to "<<"
*	or
*	from ">text.txt" to ">"
*/

static void	fix_op(char **arr, int i, char **new, int j)
{
	if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
		new[j] = ft_strdup("<");
	else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
		new[j] = ft_strdup("<<");
	else if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
		new[j] = ft_strdup(">");
	else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
		new[j] = ft_strdup(">>");
}

/*	Create new string to get the delimiter or file path
*	separated from the oerator
*	from "<<EOF" to "EOF"
*	or
*	from ">text.txt" to "text.txt"
*/

static void	fix_file_delim(char **arr, int i, char **new, int j)
{
	if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
		new[j] = ft_strdup(&arr[i][1]);
	else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
		new[j] = ft_strdup(&arr[i][2]);
	else if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
		new[j] = ft_strdup(&arr[i][1]);
	else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
		new[j] = ft_strdup(&arr[i][2]);
}

/*	To handle if there is no space between
*		- hd/hd delimiter
*		- file out / file path
*		- file append / file path
*	"<< EOF" work by default, this fct fix "<<EOF" to "<< EOF"
*/

char	**space_fix(char **arr, int i, int j, int count)
{
	char	**new;

	count = count_file_hd(arr);
	if (count == 0)
		return (arr);
	new = (char **)malloc(sizeof(char *) * (count_str(arr) + count + 1));
	if (new == NULL)
		exit(1);
	while (arr[i] != NULL)
	{
		if (is_opt(arr[i]) == 0 && (arr[i][0] == '<' || arr[i][0] == '>'))
		{
			fix_op(arr, i, new, j);
			j++;
			fix_file_delim(arr, i, new, j);
		}
		else
			new[j] = ft_strdup(arr[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	ft_memfreeall((void **)arr);
	return (new);
}
