/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:51:38 by home              #+#    #+#             */
/*   Updated: 2022/02/14 16:34:20 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Realloc the initial array (user input separate by space as delim)
*	after each node creation, in order to remove prefix and user input
*	until suffix (excluded)
*/

static char	**realloc_arr(t_list *node, char **arr, int start)
{
	char		**new;
	int			i;
	int			count;

	i = 0;
	if (node->suffix == FILE_OUT || node->suffix == FILE_APPEND)
		start += 2;
	if (arr == NULL)
		return (NULL);
	count = count_str(arr);
	if ((start >= count || start == count - 1) && ft_memfreeall((void **)arr))
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (count - start + 1));
	if (new == NULL && ft_memfreeall((void **)arr))
		return (NULL);
	while (arr[start + i] != NULL)
	{
		new[i] = ft_strdup(arr[start + i]);
		i++;
	}
	new[i] = NULL;
	ft_memfreeall((void **)arr);
	return (new);
}

/*	Fill each node's data
*		i : prefix operator index (end)
*/

static void	fill_data(t_list *node, char **arr, int i)
{
	if (node->prefix == -1 && node->suffix == -1)
		get_fix(node, arr, i);
	if (node->cmd == NULL)
		get_cmd(node, arr, i);
	if (node->cmd != NULL)
		is_builtin(node);
	if ((node->cmd != NULL && node->cmd[0] != NULL)
		&& node->builtin == false && node->bin_path == NULL)
		get_path(node);
	if (node->prefix == FILE_IN
		|| node->suffix == FILE_OUT || node->suffix == FILE_APPEND)
		get_file_path(node, arr, i);
	if (node->filein_path != NULL || node->fileout_path != NULL)
		is_file_accessible(node);
	if (node->prefix == HEREDOC && node->hd_delimiter == NULL)
		heredoc_delimiter(node, arr);
}

/*	Set defaults values for the parser's data structure */

void	init_data(t_list *node, char *readline, t_env *env)
{
	static int	read_index;

	node->env = env;
	node->cmd = NULL;
	node->bin_path = NULL;
	node->filein_path = NULL;
	node->fileout_path = NULL;
	node->hd_delimiter = NULL;
	node->readline = readline;
	node->read_index = &read_index;
	node->prefix = -1;
	node->suffix = -1;
	node->builtin = false;
	node->filein_access = false;
	node->fileout_access = false;
	node->quote_cmd = 0;
	node->quote_in = 0;
	node->quote_out = 0;
}

static int	set_var(int *q, int *i, char *str)
{
	if (str == NULL)
	{
		q[0] = 0;
		q[1] = 0;
	}
	else
	{
		q[0] += contain_quote(str, '\'');
		q[1] += contain_quote(str, '\"');
	}
	if (i != NULL)
		*i = -1;
	return (1);
}

/*	Parse the user input :
*		Separate each commands (Tokenization)
*		Each Token :
*			- contains = cmd, flags, inputs, path of the binary..
*			- is a node in the linked list
*/

t_list	*parser(char *cmd, t_env *env, int i, t_list *list)
{
	t_list	*node;
	char	**arr;
	int		q[2];

	set_var(q, NULL, NULL);
	arr = space_fix(ft_split(cmd, ' '), 0, 0, 0);
	while (arr[i] != NULL && set_var(q, NULL, arr[i]))
	{
		if (((i > 0 && is_opt(arr[i])) || arr[i + 1] == NULL)
			&& q[0] % 2 == 0 && q[1] % 2 == 0)
		{
			node = ft_lstnew();
			if (node == NULL && lst_clear_data(&list, NULL, NULL)
				&& ft_memfreeall((void **)arr))
				return (NULL);
			init_data(node, cmd, env);
			fill_data(node, arr, i);
			ft_lstadd_back(&list, node);
			arr = realloc_arr(node, arr, i);
			if (set_var(q, &i, NULL) && arr == NULL)
				break ;
		}
		i++;
	}
	return (list);
}
